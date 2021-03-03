/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
#include <cstring>

#include "swiper/swiper.hpp"

#ifdef __SANITIZE_ADDRESS__
static bool PropReversible(size_t seed, const char *password) {
    char hash[25];
    memset(hash, 0, sizeof(hash));
    swiper::Encrypt(hash, seed, password);
    char password2[12];
    memset(password2, 0, sizeof(password2));
    swiper::Decrypt(password2, hash);
    return strcmp(password2, password) == 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    const auto seed = size_t(Data[0] % 16);
    const uint8_t *Data2 = Data + 1;
    Size--;

    char password[12];
    const auto password_sz = sizeof(password);
    memset(password, 0, password_sz);
    auto password_len = Size;

    if (password_len > password_sz - 1) {
        password_len = password_sz - 1;
    }

    memcpy(password, Data2, password_len);
    assert(PropReversible(seed, password));
    return 0;
}
#endif
