/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
#include <cstring>

#include "swiper/swiper.hpp"

int main() {
    const auto password = "monke";

    for (auto i = 0; i < 16; i++) {
        auto hash = std::string(24, '\0');
        swiper::Encrypt(hash, i, password);
        const auto password2 = std::string(11, '\0');
        swiper::Decrypt(password2, hash);
        assert(password2 == password);
    }
}
