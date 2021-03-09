/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace swiper {
    namespace {
        uint8_t xlat[28] = {
            0x64, 0x73, 0x66, 0x64,
            0x3b, 0x6b, 0x66, 0x6f,
            0x41, 0x2c, 0x2e, 0x69,
            0x79, 0x65, 0x77, 0x72,
            0x6b, 0x6c, 0x64, 0x4a,
            0x4b, 0x44, 0x48, 0x53,
            0x55, 0x42, 0x73, 0x00
        };

        template <class T>
        typename std::enable_if<std::is_arithmetic<T>::value, T>::type
        parse_digit(T t) {
            if (t < (T)(58)) {
                return t - (T)(48);
            }

            return t - (T)(87);
        }

        inline int parse_dec(const char *pair) {
            return 10 * parse_digit(int(pair[0])) + parse_digit(int(pair[1]));
        }

        inline uint8_t parse_hex(const char *pair) {
            return 0x10 * parse_digit(pair[0]) + parse_digit(pair[1]);
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
            --n;
        }
    }

    void Decrypt(char *password, const char *hash) noexcept {
        auto j = int(strlen(hash)) - 2;

        if (j == 0) {
            return;
        }

        auto i = j / 2 - 1;
        auto seed = i + parse_dec(hash);

        for (;;) {
            password[i--] = xlat[seed--] ^ parse_hex(hash + j);

            if (i == -1) {
                break;
            }

            j -= 2;
        }
    }
}
