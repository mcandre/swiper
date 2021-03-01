/**
 * @copyright 2021 YelloSoft
 */

#include <array>
#include <iostream>
#include <sstream>
#include <string>

#include "swiper/swiper.hpp"

static const std::array<int, 53> xlat = {
    0x64, 0x73, 0x66, 0x64, 0x3b, 0x6b, 0x66, 0x6f,
    0x41, 0x2c, 0x2e, 0x69, 0x79, 0x65, 0x77, 0x72,
    0x6b, 0x6c, 0x64, 0x4a, 0x4b, 0x44, 0x48, 0x53,
    0x55, 0x42, 0x73, 0x67, 0x76, 0x63, 0x61, 0x36,
    0x39, 0x38, 0x33, 0x34, 0x6e, 0x63, 0x78, 0x76,
    0x39, 0x38, 0x37, 0x33, 0x32, 0x35, 0x34, 0x6b,
    0x3b, 0x66, 0x67, 0x38, 0x37
};

std::string swiper::Encrypt(uint *prng_seed, const std::string &password) {
    auto seed = int(rand_r(prng_seed) % 16);

    auto hash = std::stringstream();
    hash.setf(std::ios::dec, std::ios::basefield);
    hash.width(2);
    hash.fill('0');
    hash << seed;

    for (auto &p_char : password) {
        const auto p = int(p_char);
        hash.setf(std::ios::hex, std::ios::basefield);
        hash.width(2);
        hash.fill('0');
        hash << int(p ^ xlat.at(size_t((seed++) % int(xlat.size()))));
    }

    return hash.str();
}

std::optional<std::string> swiper::Decrypt(const std::string &hash) {
    auto len = hash.length();

    if (len < 2 || len > 24 || len % 2 != 0) {
        return std::nullopt;
    }

    errno = 0;
    auto seed = std::stoi(hash.substr(0, 2), nullptr, 10);

    if (errno != 0) {
        return nullptr;
    }

    auto password = std::stringstream();

    for (size_t i = 2; i < len; i += 2) {
        errno = 0;
        const auto c = std::stoi(hash.substr(i, 2), nullptr, 16);

        if (errno != 0) {
            return std::nullopt;
        }

        password << char(c ^ xlat.at(size_t((seed++) % int(xlat.size()))));
    }

    return password.str();
}
