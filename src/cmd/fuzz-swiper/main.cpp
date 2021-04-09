/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <algorithm>
#include <cassert>
#include <cstring>

#include "swiper/swiper.hpp"

#ifdef __SANITIZE_ADDRESS__
/**
 * @brief FormatDecPair renders decimal pairs.
 *
 * @param result out buffer, min 3 characters
 * @param offset buffer write index
 * @param v value
 */
static void FormatDecPair(char* result, size_t offset, size_t v) noexcept {
    char remainder = v % 10;
    result[offset] = (v - remainder) / 10 + 48;
    result[offset + 1]= remainder + 48;
}

/**
 * @brief FormatHexDigit renders a hexadecimal digit.
 *
 * @param v value
 */
static auto FormatHexDigit(unsigned char v) noexcept {
    return v + 48 + 7 * (v > 9);
}

/**
 * @brief FormatHexPair renders hexadecimal pairs.
 *
 * @param result out buffer, min 3 characters
 * @param offset buffer write index
 * @param v value
 */
static void FormatHexPair(char* result, size_t offset, unsigned char v) noexcept {
    auto remainder = v % 16;
    result[offset] = FormatHexDigit((v - remainder) / 16);
    result[offset + 1]= FormatHexDigit(remainder);
}

/**
 * @brief Encrypt generates Cisco type 7 hashes.
 *
 * @param hash out buffer, min 2 * (1 + password_len), non-null termated
 * @param seed key index in [0, 16)
 * @param password_len string length of password
 * @param password ASCII, max length 11
 */
static void Encrypt(char* hash, size_t seed, size_t password_len, const char* password) noexcept {
    if (password_len > 11) {
        password_len = 11;
    }

    FormatDecPair(hash, 0, seed);
    auto xlat_seeded = swiper::Xlat + seed;

    for (auto i = size_t(0), j = size_t(2); i < password_len; i++, j += 2) {
        const auto c = static_cast<unsigned char>(password[i] ^ xlat_seeded[i]);
        FormatHexPair(hash, j, c);
    }
}

/**
 * @brief PropReversible tests the symmetric nature of the Cisco type 7 cryptographic algorithm.
 *
 * @param seed key index in [0, 16)
 * @param password_len string length of password
 * @param password ASCII, max length 11
 */
static bool PropReversible(size_t seed, size_t password_len, const char* password) {
    if (password_len == 0) {
        return true;
    }

    char hash[25];
    Encrypt(hash, seed, password_len, password);
    const auto hash_len = 2 * (password_len + 1);
    hash[hash_len] = '\0';
    char password2[12];
    swiper::Decrypt(password2, hash_len, hash);
    password2[hash_len / 2 - 1] = '\0';
    return strcmp(password2, password) == 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size < 2 || Data[1] == '\0') {
        return 0;
    }

    const auto seed = size_t(Data[0]) % 16;
    const char *Data2 = (char*)(Data) + 1;
    auto password_len = size_t(Size - 1);

    if (password_len > 11) {
        password_len = 11;
    }

    char password[12];
    std::copy(Data2, Data2 + password_len, password);
    password[password_len] = '\0';
    assert(PropReversible(seed, password_len, password));
    return 0;
}
#endif
