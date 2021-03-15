/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

#include <cstddef>
#include <type_traits>

namespace swiper {
    namespace {
        inline size_t ParseDecDigit(char c) noexcept {
            return size_t(c - '\x30');
        }

        inline uint8_t ParseHexDigit(char c) noexcept {
            if (c & '\x40') {
                return uint8_t(c - '\x57');
            }

            return uint8_t(c - '\x30');
        }

        inline size_t ParseDecPair(const std::string& pair, size_t offset) noexcept {
            return ParseDecDigit(pair[offset]) * size_t(10) + ParseDecDigit(pair[offset + 1]);
        }

        inline uint8_t ParseHexPair(const std::string& pair, size_t offset) noexcept {
            return ParseHexDigit(pair[offset]) * uint8_t(16) + ParseHexDigit(pair[offset + 1]);
        }
    }

    void WarmCache(std::string& password, const std::string& hash, int32_t n) noexcept {
        while (--n != 0) {
            Decrypt(password, hash);
        }
    }

    void Decrypt(std::string& password, const std::string& hash) noexcept {
        const auto xlat_seeded = Xlat + ParseDecPair(hash, 0);
        auto j = hash.length();
        auto i = j / 2 - 1;

        for (;;) {
            --i;
            j -= 2;
            password[i] = xlat_seeded[i] ^ ParseHexPair(hash, j);

            if (i == 0) {
                return;
            }
        }
    }
}
