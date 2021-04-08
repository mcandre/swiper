/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

namespace swiper {
    namespace {
        template<class T>
        auto ParseDecPair(const T* pair) noexcept {
            return pair[0] & static_cast<T>(1) ? pair[1] - static_cast<T>(38) : pair[1] - static_cast<T>(48);
        }

        template<class T>
        auto ParseHexDigit(T v) noexcept {
            return v & static_cast<T>(64) ? v - static_cast<T>(55) : v - static_cast<T>(48);
        }

        template<class T>
        auto ParseHexPair(const T* pair) noexcept {
            return static_cast<T>(16) * ParseHexDigit(pair[0]) + ParseHexDigit(pair[1]);
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
