/**
 * @copyright 2021 YelloSoft
 */

#include <array>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "swiper/swiper.hpp"

static const uint8_t xlats[16][11] = {
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
};

void swiper::Encrypt(char *hash, unsigned int prng_seed, const char *password) {
    std::uniform_int_distribution distribution(0, 15);
    std::default_random_engine rng(prng_seed);
    auto seed = size_t(distribution(rng));

    auto hash_buf = std::stringstream();
    hash_buf.setf(std::ios::dec, std::ios::basefield);
    hash_buf.width(2);
    hash_buf.fill('0');
    hash_buf << seed;

    auto xlat = xlats[seed];
    seed = 0;

    hash_buf.setf(std::ios::hex, std::ios::basefield);
    hash_buf.width(2);
    hash_buf.fill('0');

    const auto len = strlen(password);

    for (size_t i = 0; i < len && i < 12; i++) {
        hash_buf << uint8_t(xlat[seed++] ^ password[i]);
    }

    auto hash_s = hash_buf.str();
    hash_s.copy(hash, hash_s.length(), 0);
}

static inline uint8_t parse_digit(char c) {
    switch(c) {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case 'a':
        return 10;
    case 'b':
        return 11;
    case 'c':
        return 12;
    case 'd':
        return 13;
    case 'e':
        return 14;
    default:
        return 15;
    }
}

static uint8_t parse_int(const char *pair) {
    return parse_digit(pair[0]) * 10 + parse_digit(pair[1]);
}

static inline uint8_t parse_hex(const char *pair) {
    return parse_digit(pair[0]) * 16 + parse_digit(pair[1]);
}

void swiper::Decrypt(char *password, const char *hash) {
    auto seed = size_t(parse_int(hash));
    const auto xlat = xlats[seed];
    const auto len = strlen(hash);
    seed = len/2;

    for (size_t i = len - 2; i > 1; i -= 2) {
        const auto c = parse_hex(hash + i);
        password[seed] = xlat[seed--] ^ c;
    }
}
