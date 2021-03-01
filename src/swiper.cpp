/**
 * @copyright 2021 YelloSoft
 */

#include <array>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

#include "swiper/swiper.hpp"

static const std::array<std::array<uint8_t, 11>, 16> xlats = {{
    {
        0x64, 0x73, 0x66, 0x64,
        0x3b, 0x6b, 0x66, 0x6f,
        0x41, 0x2c, 0x2e
    },
    {
        0x73, 0x66, 0x64, 0x3b,
        0x6b, 0x66, 0x6f, 0x41,
        0x2c, 0x2e, 0x69
    },
    {
        0x66, 0x64, 0x3b, 0x6b,
        0x66, 0x6f, 0x41, 0x2c,
        0x2e, 0x69, 0x79
    },
    {
        0x64, 0x3b, 0x6b, 0x66,
        0x6f, 0x41, 0x2c, 0x2e,
        0x69, 0x79, 0x65
    },
    {
        0x3b, 0x6b, 0x66, 0x6f,
        0x41, 0x2c, 0x2e, 0x69,
        0x79, 0x65, 0x77
    },
    {
        0x6b, 0x66, 0x6f, 0x41,
        0x2c, 0x2e, 0x69, 0x79,
        0x65, 0x77, 0x72
    },
    {
        0x66, 0x6f, 0x41, 0x2c,
        0x2e, 0x69, 0x79, 0x65,
        0x77, 0x72, 0x6b
    },
    {
        0x6f, 0x41, 0x2c, 0x2e,
        0x69, 0x79, 0x65, 0x77,
        0x72, 0x6b, 0x6c
    },
    {
        0x41, 0x2c, 0x2e, 0x69,
        0x79, 0x65, 0x77, 0x72,
        0x6b, 0x6c, 0x64
    },
    {
        0x2c, 0x2e, 0x69, 0x79,
        0x65, 0x77, 0x72, 0x6b,
        0x6c, 0x64, 0x4a
    },
    {
        0x2e, 0x69, 0x79, 0x65,
        0x77, 0x72, 0x6b, 0x6c,
        0x64, 0x4a, 0x4b
    },
    {
        0x69, 0x79, 0x65, 0x77,
        0x72, 0x6b, 0x6c, 0x64,
        0x4a, 0x4b, 0x44
    },
    {
        0x79, 0x65, 0x77, 0x72,
        0x6b, 0x6c, 0x64, 0x4a,
        0x4b, 0x44, 0x48
    },
    {
        0x65, 0x77, 0x72, 0x6b,
        0x6c, 0x64, 0x4a, 0x4b,
        0x44, 0x48, 0x53
    },
    {
        0x77, 0x72, 0x6b, 0x6c,
        0x64, 0x4a, 0x4b, 0x44,
        0x48, 0x53, 0x55
    },
    {
        0x72, 0x6b, 0x6c, 0x64,
        0x4a, 0x4b, 0x44, 0x48,
        0x53, 0x55, 0x42
    }
}};

std::string swiper::Encrypt(uint *prng_seed, const std::string &password) {
    auto seed = size_t(rand_r(prng_seed) % 16);

    auto hash = std::stringstream();
    hash.setf(std::ios::dec, std::ios::basefield);
    hash.width(2);
    hash.fill('0');
    hash << seed;

    auto xlat = xlats.at(seed);
    seed = 0;

    for (size_t i = 0; i < password.length() && i < 12; i++) {
        const auto p = uint8_t(password.at(i));
        const auto c = p ^ xlat.at(seed++);
        hash.setf(std::ios::hex, std::ios::basefield);
        hash.width(2);
        hash.fill('0');
        hash << c;
    }

    return hash.str();
}

std::string swiper::Decrypt(const std::string &hash) {
    auto seed_int = std::stoi(hash.substr(0, 2), nullptr, 10);
    auto seed = size_t(seed_int);
    auto xlat = xlats.at(seed);
    seed = 0;

    auto password = std::stringstream();

    auto len = hash.length();

    for (size_t i = 2; i < len; i += 2) {
        const auto c = std::stoi(hash.substr(i, 2), nullptr, 16);
        password << char(c ^ xlat.at(seed++));
    }

    return password.str();
}
