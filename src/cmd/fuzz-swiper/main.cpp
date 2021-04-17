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
static void FormatDecPair(unsigned char* result, size_t offset, size_t v) noexcept {
    unsigned char remainder = v % 10;
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
static void FormatHexPair(unsigned char* result, size_t offset, unsigned char v) noexcept {
    auto remainder = v % 16;
    result[offset] = FormatHexDigit((v - remainder) / 16);
    result[offset + 1]= FormatHexDigit(remainder);
}

/**
 * @brief Xlat is a fixed XOR key.
 */
static constexpr char Xlat[32] = {
    0x64, 0x73, 0x66, 0x64,
    0x3b, 0x6b, 0x66, 0x6f,
    0x41, 0x2c, 0x2e, 0x69,
    0x79, 0x65, 0x77, 0x72,
    0x6b, 0x6c, 0x64, 0x4a,
    0x4b, 0x44, 0x48, 0x53,
    0x55, 0x42, 0x73, 0x00,
    0x00, 0x00, 0x00, 0x00
};

/**
 * @brief Encrypt generates Cisco type 7 hashes.
 *
 * @param hash out buffer, min 2 * (1 + password_len), non-null termated
 * @param seed key index in [0, 16)
 * @param password_len string length of password
 * @param password ASCII, max length 11
 */
static void Encrypt(unsigned char* hash, size_t seed, size_t password_len, const unsigned char* password) noexcept {
    if (password_len > 11) {
        password_len = 11;
    }

    FormatDecPair(hash, 0, seed);
    auto xlat_seeded = Xlat + seed;

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
static bool PropReversible(size_t seed, size_t password_len, const unsigned char* password) {
    if (password_len == 0) {
        return true;
    }

    char password_signed[12];
    std::copy(password, password + password_len + 1, password_signed);
    unsigned char hash[25];
    Encrypt(hash, seed, password_len, password);
    const auto hash_len = 2 * (password_len + 1);
    hash[hash_len] = '\0';
    unsigned char password2[12];
    swiper::Decrypt(password2, hash_len, hash);
    const auto password2_len = hash_len / 2 - 1;
    password2[password2_len] = '\0';
    char password2_signed[12];
    std::copy(password2, password2 + password2_len + 1, password2_signed);
    return strcmp(password2_signed, password_signed) == 0;
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

    unsigned char password[12];
    std::copy(Data2, Data2 + password_len, password);
    password[password_len] = '\0';
    assert(PropReversible(seed, password_len, password));
    return 0;
}
#endif
