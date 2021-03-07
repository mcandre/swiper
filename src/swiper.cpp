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

static const short int xlat[32] = {
    0x64, 0x73, 0x66, 0x64,
    0x3b, 0x6b, 0x66, 0x6f,
    0x41, 0x2c, 0x2e, 0x69,
    0x79, 0x65, 0x77, 0x72,
    0x6b, 0x6c, 0x64, 0x4a,
    0x4b, 0x44, 0x48, 0x53,
    0x55, 0x42, 0x73, 0x00,
    0x00, 0x00, 0x00, 0x00
};

namespace swiper {
    namespace {
        inline int parse_digit(char c) {
            if (c > '/' && c < ':') {
                return c - '0';
            }

            return 10 + (c - 'a');
        }

        inline short int parse_dec(const char *pair) {
            return 10 * parse_digit(pair[0]) + parse_digit(pair[1]);
        }

        inline int parse_hex(const char *pair) {
            return 16 * parse_digit(pair[0]) + parse_digit(pair[1]);
        }
    }

    void Encrypt(char *hash, short int seed, const char *password) noexcept {
        auto hash_buf = std::stringstream();
        hash_buf.setf(std::ios::dec, std::ios::basefield);
        hash_buf << std::setw(2) << std::setfill('0') << seed;
        hash_buf.setf(std::ios::hex, std::ios::basefield);
        auto len = int(strlen(password));

        if (len > 11) {
            len = 11;
        }

        for (auto i = 0; i < len; i++) {
            auto c = xlat[seed++] ^ uint8_t(password[i]);
            hash_buf << std::setw(2) << std::setfill('0') << c;
        }

        auto hash_s = hash_buf.str();
        hash_s.copy(hash, hash_s.length(), 0);
    }

    void WarmCache(char *password, const char *hash, int n) noexcept {
        while (n != 0) {
            swiper::Decrypt(password, hash);
            n--;
        }
    }

    void Decrypt(char *password, const char *hash) noexcept {
        const char *h = 2 + hash;
        const auto len = int(strlen(h)) >> 1;

        if (len == 0) {
            return;
        }

        auto i = len - 1;
        auto j = i << 1;
        auto seed = parse_dec(hash) + (short int) i;

        for (;;) {
            password[i] = xlat[seed--] ^ parse_hex(h + j);

            if (i == 0) {
                break;
            }

            i--;
            j -= 2;
        }
    }
}
