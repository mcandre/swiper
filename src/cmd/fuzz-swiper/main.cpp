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

static char FormatHexDigit(char v) noexcept {
    return v < 10 ? v + 48 : v + 87;
}

static void FormatHexPair(char* result, size_t offset, char v) noexcept {
    char remainder = v % 16;
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
        const auto c = char(password[i] ^ xlat_seeded[i]);
        FormatHexPair(hash, j, c);
    }
}

static bool PropReversible(size_t seed, size_t password_len, const char* password) {
    if (password_len == 0) {
        return true;
    }

    char hash[34] __attribute__((aligned (16)));
    memset(hash, 0, sizeof(hash));
    Encrypt(hash, seed, password_len, password);
    char password2[16] __attribute__((aligned (16)));
    swiper::Decrypt(password2, hash);
    password2[strlen(hash) / 2 - 1] = '\0';
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

    char password[16] __attribute__((aligned (16)));
    memset(password, 0, sizeof(password));
    std::copy(Data2, Data2 + password_len, password);
    assert(PropReversible(seed, password_len, password));
    return 0;
}
#endif
