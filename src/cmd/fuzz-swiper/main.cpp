/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
#include <cstring>

#include "swiper/swiper.hpp"

#ifdef __SANITIZE_ADDRESS__
template <class T>
static uint8_t FormatDigit(T t) noexcept {
    if (t > T(9)) {
        return  uint8_t(t) + '\x57';
    }

    return uint8_t(t) + '\x30';
}

template <class T>
static void FormatPair(char *result, size_t offset, T value, T base) noexcept {
    T remainder = value % base;
    result[offset] = FormatDigit((value - remainder) / base);
    result[offset + 1]= FormatDigit(remainder);
}

static void Encrypt(char *hash, size_t seed, const std::string_view& password) noexcept {
    auto len = password.length();

    if (len > size_t(11)) {
        len = size_t(11);
    }

    FormatPair(hash, 0, seed, size_t(10));
    auto xlat_seeded = swiper::Xlat + seed;

    for (auto i = size_t(0), j = size_t(2); i < len; i++, j += 2) {
        const auto c = uint8_t(password[i] ^ xlat_seeded[i]);
        FormatPair(hash, j, c, uint8_t(16));
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
    if (Size < size_t(2) || Data[1] == '\0') {
        return 0;
    }

    const auto seed = size_t(Data[0]) % 16;
    const char *Data2 = 1 + (char*) Data;
    auto password_len = size_t(Size - 1);

    if (password_len > size_t(11)) {
        password_len = size_t(11);
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
