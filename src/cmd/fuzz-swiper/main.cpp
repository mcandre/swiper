/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
#include <cstring>

#include "swiper/swiper.hpp"

#ifdef __SANITIZE_ADDRESS__
static bool PropReversible(size_t seed, const std::string& password) {
    auto hash = std::string(2 * (1 + password.length()), '\0');
    swiper::Encrypt(hash, seed, password);
    auto password2 = std::string(password.length(), '\0');
    swiper::Decrypt(password2, hash);
    return password2 == password;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    const auto seed = size_t(Data[0]) % 16;
    const uint8_t *Data2 = 1 + Data;
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
