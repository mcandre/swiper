/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
#include <cstring>
#include <random>

#include "swiper/swiper.hpp"

#ifdef __SANITIZE_ADDRESS__
static bool PropReversible(const char *password) {
    const auto prng_seed = (unsigned int)(time(nullptr));
    char hash[25];
    swiper::Encrypt(hash, prng_seed, password);
    hash[2 * (1 + strlen(password))] = '\0';
    char password2[12];
    swiper::Decrypt(password2, hash);
    password2[strlen(hash)/2 - 1] = '\0';
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
    assert(PropReversible(password));
    return 0;
}
#endif
