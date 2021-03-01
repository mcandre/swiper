/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cstring>
#include <iostream>
#include <random>
#include <sstream>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <string_view>
#include <vector>

#include "swiper/swiper.hpp"

#ifdef __SANITIZE_ADDRESS__
static bool PropReversible(const char *password) {
    const auto prng_seed = (unsigned int)(time(nullptr));
    char hash[25];

    swiper::Encrypt(hash, prng_seed, password);

    char password2[12];
    swiper::Decrypt(password2, hash);
    return strcmp(password2, password) == 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    char password[12];
    const auto password_sz = sizeof(password);
    auto password_len = Size;

    if (password_len > password_sz - 1) {
        password_len = password_sz - 1;
    }

    memcpy(password, Data, password_len);
    password[password_len] = '\0';
    PropReversible(password);
    return 0;
}
#endif
