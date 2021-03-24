/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
#include <cstring>

#include "swiper/swiper.hpp"

#ifdef __SANITIZE_ADDRESS__
static void FormatDecPair(char *result, size_t offset, size_t v) noexcept {
    char remainder = v % 10;
    result[offset] = (v - remainder) / 10 + 48;
    result[offset + 1]= remainder + 48;
}

static char FormatHexDigit(char v) noexcept {
    return v < 10 ? v + 48 : v + 87;
}

static void FormatHexPair(char *result, size_t offset, char v) noexcept {
    char remainder = v % 16;
    result[offset] = FormatHexDigit((v - remainder) / 16);
    result[offset + 1]= FormatHexDigit(remainder);
}

static void Encrypt(char *hash, size_t seed, const std::string_view& password) noexcept {
    auto len = password.length();

    if (len > 11) {
        len = 11;
    }

    FormatDecPair(hash, 0, seed);
    auto xlat_seeded = swiper::Xlat + seed;

    for (auto i = size_t(0), j = size_t(2); i < len; i++, j += 2) {
        const auto c = char(password[i] ^ xlat_seeded[i]);
        FormatHexPair(hash, j, c);
    }
}

static bool PropReversible(size_t seed, const std::string_view& password) {
    if (password == "") {
        return true;
    }

    char hash[25];
    Encrypt(hash, seed, password);
    hash[2 * (password.length() + 1)] = '\0';
    char password2[12];
    swiper::Decrypt(password2, std::string_view(hash));
    password2[strlen(hash) / 2 - 1] = '\0';
    return password == password2;
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

    for (auto i = size_t(1); i < password_len; i++) {
        if (Data2[i] == '\0') {
            password_len = i - 1;
            break;
        }
    }

    assert(PropReversible(seed, std::string_view(Data2, password_len)));
    return 0;
}
#endif
