/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <algorithm>
#include <cassert>
#include <cstring>

#include "swiper/swiper.hpp"

#ifdef __SANITIZE_ADDRESS__
static void FormatDecPair(char* result, size_t offset, size_t v) noexcept {
    char remainder = v % 10;
    result[offset] = (v - remainder) / 10 + 48;
    result[offset + 1]= remainder + 48;
}

static auto FormatHexDigit(unsigned char v) noexcept {
    return v + 48 + 7 * (v > 9);
}

static void FormatHexPair(char* result, size_t offset, unsigned char v) noexcept {
    auto remainder = v % 16;
    result[offset] = FormatHexDigit((v - remainder) / 16);
    result[offset + 1]= FormatHexDigit(remainder);
}

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
