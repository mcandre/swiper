/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cstring>
#include <iostream>
#include <sstream>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <string_view>
#include <vector>

#include "swiper/swiper.hpp"

static bool PropReversible(const std::string &password) {
    auto prng_seed = uint(time(nullptr));
    const auto hash = swiper::Encrypt(&prng_seed, password);
    const auto password2 = swiper::Decrypt(hash);

    if (!password2.has_value()) {
        return false;
    }

    return password.compare(password2.value()) == 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    char password_cstr[12];
    const auto password_cstr_sz = sizeof(password_cstr);
    auto password_cstr_len = Size;

    if (password_cstr_len > password_cstr_sz - 1) {
        password_cstr_len = password_cstr_sz - 1;
    }

    memcpy(password_cstr, Data, password_cstr_len);
    password_cstr[password_cstr_len] = '\0';
    const auto password = std::string(password_cstr);
    PropReversible(password);
    return 0;
}
