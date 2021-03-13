/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
#include <cstring>

#include "swiper/swiper.hpp"

int main() {
    const auto password = std::string("monke");

    for (auto i = 0; i < 16; i++) {
        auto hash = std::string(2 * (1 + password.length()), '\0');
        swiper::Encrypt(hash, i, password);
        auto password2 = std::string(hash.length() / 2 - 1, '\0');
        swiper::Decrypt(password2, hash);
        assert(password2 == password);
    }
}
