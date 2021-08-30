/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#ifdef __SANITIZE_ADDRESS__
#include <algorithm>
#include <cassert>
#include <cstring>

#include "swiper/swiper.hpp"

/**
 * @brief FormatDecPair renders decimal pairs.
 *
 * @param result out buffer, min 3 characters
 * @param offset buffer write index
 * @param v value
 */
static void FormatDecPair(uint8_t *result, size_t offset, size_t v) noexcept {
    const uint8_t remainder = v % 10;
    result[offset] = (v - remainder) / 10 + 48;
    result[offset + 1] = remainder + 48;
}

/**
 * @brief FormatHexDigit renders a hexadecimal digit.
 *
 * @param v value
 */
static auto FormatHexDigit(uint8_t v) noexcept {
    return uint8_t(7) * uint8_t(v > uint8_t(9)) +
           v +
           uint8_t(48);
}

/**
 * @brief FormatHexPair renders hexadecimal pairs.
 *
 * @param result out buffer, min 3 characters
 * @param offset buffer write index
 * @param v value
 */
static void FormatHexPair(uint8_t *result, size_t offset, uint8_t v) noexcept {
    const auto remainder = v % 16;
    result[offset] = FormatHexDigit((v - remainder) / 16);
    result[offset + 1] = FormatHexDigit(remainder);
}

/**
 * @brief Xlat is a fixed XOR key.
 */
static constexpr uint8_t Xlat[32] = {
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
static void Encrypt(uint8_t *hash, size_t seed, size_t password_len, const uint8_t *password) noexcept {
    password_len = std::min(size_t(11), password_len);

    FormatDecPair(hash, 0, seed);
    const auto *k = Xlat + seed;

    for (auto i = size_t(0), j = size_t(2); i < password_len; i++, j += 2) {
        const auto c = uint8_t(password[i] ^ k[i]);
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
static bool PropReversible(size_t seed, size_t password_len, const uint8_t *password) {
    if (password_len == 0) {
        return true;
    }

    char password_signed[12];
    std::copy(password, password + password_len + 1, password_signed);
    uint8_t hash[25];
    Encrypt(hash, seed, password_len, password);
    const auto hash_len = 2 * (password_len + 1);
    hash[hash_len] = '\0';
    uint8_t password2[12];
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
    const auto password_len = std::min(size_t(11), size_t(Size - 1));

    uint8_t password[12];
    std::copy(Data + 1, Data + 1 + password_len, password);
    password[password_len] = '\0';
    assert(PropReversible(seed, password_len, password));
    return 0;
}
#endif
