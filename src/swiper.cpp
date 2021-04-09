/**
 * @copyright 2020 YelloSoft
*/




#include <iostream>



#include "swiper/swiper.hpp"

namespace swiper {
    namespace {
        template<class T>
        auto ParseDecPair(const T* pair) noexcept {
            // Branching benchmarks faster here than multiplication
            // return 10 * (pair[0] & 1) + (pair[1] & 0x0f);
            return pair[0] & 1 ? pair[1] - 38 : pair[1] - 48;
        }

        template<class T>
        auto ParseHexDigit(const T v) noexcept {
            // Branching benchmarks faster here than multiplication
            // return (v & 0x0f) + 9 * (v >> 6);
            return (v & 64) ? v - 55 : v - 48;
        }

        template<class T>
        auto ParseHexPair(const T* pair) noexcept {
            return 16 * ParseHexDigit(pair[0]) + ParseHexDigit(pair[1]);
        }
    }

    void Decrypt(char* password, size_t hash_len, const char* hash) noexcept {
        auto i = hash_len / 2 - 2;
        auto k = Xlat + ParseDecPair(hash);
        auto c = hash + 2;

        for (;;) {
            *password++ = static_cast<char>(*k++ ^ ParseHexPair(c));

            if (i-- == 0) {
                return;
            }

            c += 2;
        }
    }
}
