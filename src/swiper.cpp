/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"





#include <iostream>


#include <type_traits>

namespace swiper {
    namespace {
        inline size_t ParseDecDigit(size_t v) noexcept {
            return v - size_t(48);
        }

        inline uint8_t ParseHexDigit(uint8_t v) noexcept {
            if (v & uint8_t(64)) {
                return v - uint8_t(87);
            }

            return v - uint8_t(48);
        }

        inline size_t ParseDecPair(const std::string& pair, size_t offset) noexcept {
            return ParseDecDigit(size_t(pair[offset])) * size_t(10) + ParseDecDigit(size_t(pair[offset + 1]));
        }

        inline uint8_t ParseHexPair(const std::string& pair, size_t offset) noexcept {
            return ParseHexDigit(uint8_t(pair[offset])) * uint8_t(16) + ParseHexDigit(uint8_t(pair[offset + 1]));
        }
    }

    void WarmCache(std::string& password, const std::string& hash, int32_t n) noexcept {
        while (--n != 0) {
            Decrypt(password, hash);
        }
    }

    void Decrypt(std::string& password, const std::string& hash) noexcept {
        auto j = hash.length() - 2;

        if (j == 0) {
            return;
        }

        auto i = j / 2;
        auto xlat_seeded = Xlat + ParseDecPair(hash, 0);

        for (;;) {
            --i;
            password[i] = xlat_seeded[i] ^ ParseHexPair(hash, j);
            j -= 2;

            if (i == 0) {
                return;
            }
        }
    }
}
