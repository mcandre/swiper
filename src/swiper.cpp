/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

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

namespace swiper {
    namespace {
        inline char parse_digit(char c) {
            if (c > '/' && c < ':') {
                return c - '0';
            }

            return 10 + c - 'a';
        }

        inline size_t parse_int(const char *pair) {
            return size_t(10 * parse_digit(pair[0]) + parse_digit(pair[1]));
        }

        inline char parse_hex(const char *pair) {
            return 16 * parse_digit(pair[0]) + parse_digit(pair[1]);
        }
    }

    void Encrypt(char *hash, size_t seed, const char *password) {
        const auto xlat = xlats[seed];

        auto hash_buf = std::stringstream();
        hash_buf.setf(std::ios::dec, std::ios::basefield);
        hash_buf << std::setw(2) << std::setfill('0') << seed;
        hash_buf.setf(std::ios::hex, std::ios::basefield);

        auto len = strlen(password);

        if (len > 11) {
            len = 11;
        }

        for (auto i = 0u; i < len; i++) {
            auto c = xlat[i] ^ uint8_t(password[i]);
            hash_buf << std::setw(2) << std::setfill('0') << c;
        }

        auto hash_s = hash_buf.str();
        hash_s.copy(hash, hash_s.length(), 0);
    }

    void Decrypt(char *password, const char *hash) {
        const auto xlat = xlats[parse_int(hash)];
        const char *h = 2 + hash;
        const auto len = 11;

        for (auto i = len - 1, j = 2 * (len - 1); i != -1; i--, j -= 2) {
            const char *k = h + j;

            if (*k == '\0') {
                continue;
            }

            password[i] = xlat[i] ^ parse_hex(k);
        }
    }
}
