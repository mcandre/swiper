/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

namespace swiper {
    namespace {
        inline auto ParseDecPair(const char* pair) noexcept {
            return static_cast<size_t>(pair[0] & 1 ? pair[1] - 38 : pair[1] - 48);
        }

        inline auto ParseHexDigit(char v) noexcept {
            return v & 64 ? v - 87 : v - 48;
        }

        inline auto ParseHexPair(const char* pair) noexcept {
            return 16 * ParseHexDigit(pair[0]) + ParseHexDigit(pair[1]);
        }
    }

    void Spin(volatile uint_fast32_t n) noexcept {
        while (n-- != 0) {}
    }

    void WarmCache(char* password, size_t hash_len, const char* hash, volatile uint_fast32_t n) noexcept {
        while (n-- != 0) {
            Decrypt(password, hash_len, hash);
        }
    }

    void Decrypt(char* password, size_t hash_len, const char* hash) noexcept {
        auto i = hash_len / 2 - 2;
        auto k = Xlat + ParseDecPair(hash);
        auto c = hash + 2;

        for (;;) {
            *password++ = *k++ ^ ParseHexPair(c);

            if (i-- == 0) {
                break;
            }

            c += 2;
        }
    }
}
