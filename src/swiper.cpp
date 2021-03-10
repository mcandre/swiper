/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace swiper {
    const uint8_t Xlat[28] = {
        0x64, 0x73, 0x66, 0x64,
        0x3b, 0x6b, 0x66, 0x6f,
        0x41, 0x2c, 0x2e, 0x69,
        0x79, 0x65, 0x77, 0x72,
        0x6b, 0x6c, 0x64, 0x4a,
        0x4b, 0x44, 0x48, 0x53,
        0x55, 0x42, 0x73, 0x00
    };

    int32_t ParseDigit(char c) {
        if (c & '\x40') {
            return int32_t(c - '\x57');
        }

        return int32_t(c - '\x30');
    }

    int32_t ParseDec(const char *pair) {
        return ParseDigit(pair[0]) * 10 + ParseDigit(pair[1]);
    }

    int32_t ParseHex(const char *pair) {
        return ParseDigit(pair[0]) * 16 + ParseDigit(pair[1]);
    }

    void Encrypt(char *hash, int32_t seed, const char *password) noexcept {
        auto hash_buf = std::stringstream();
        hash_buf.setf(std::ios::dec, std::ios::basefield);
        hash_buf << std::setw(2) << std::setfill('0') << seed;
        hash_buf.setf(std::ios::hex, std::ios::basefield);
        auto len = int32_t(strlen(password));

        if (len > 11) {
            len = 11;
        }

        for (auto i = 0; i < len; i++) {
            const auto c = Xlat[seed++] ^ uint8_t(password[i]);
            hash_buf << std::setw(2) << std::setfill('0') << c;
        }

        auto hash_s = hash_buf.str();
        hash_s.copy(hash, hash_s.length(), 0);
    }

    void WarmCache(char *password, const char *hash, int32_t n) noexcept {
        while (n != 0) {
            Decrypt(password, hash);
            --n;
        }
    }

    void Decrypt(char *password, const char *hash) noexcept {
        auto j = int32_t(strlen(hash)) - 2;

        if (j == 0) {
            return;
        }

        auto i = j / 2 - 1;
        auto seed = i + ParseDec(hash);

        for (;;) {
            password[i--] = Xlat[seed--] ^ uint8_t(ParseHex(hash + j));

            j -= 2;

            if (j == 0) {
                return;
            }
        }
    }
}
