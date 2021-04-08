/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

namespace swiper {
    namespace {
        template<class T>
        auto ParseDecPair(const T* pair) noexcept {
            return pair[1] - 48 + 10 * (pair[0] & 1);
        }

        template<class T>
        auto ParseHexDigit(T v) noexcept {
            return v & 64 ? v - 55 : v - 48;
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
