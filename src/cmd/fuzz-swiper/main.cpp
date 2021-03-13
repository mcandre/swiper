/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>

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
    if (Size == size_t(0)) {
        return 0;
    }

    const auto seed = size_t(Data[0]) % 16;
    const char *Data2 = 1 + (char*) Data;
    auto password_len = size_t(Size - 1);

    if (password_len > size_t(11)) {
        password_len = size_t(11);
    }

    auto password = std::string(Data2, password_len);
    assert(PropReversible(seed, password));
    return 0;
}
#endif
