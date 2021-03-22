/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

namespace swiper {
    namespace {
        ALWAYS_INLINE size_t ParseDecPair(const char *pair) noexcept {
            return size_t(10 * pair[0] + pair[1] - 528);
        }

        ALWAYS_INLINE auto ParseHexDigit(char v) noexcept {
            return v & '\x40' ? v - '\x57' : v - '\x30';
        }

        ALWAYS_INLINE auto ParseHexPair(const char *pair) noexcept {
            return '\x10' * ParseHexDigit(pair[0]) + ParseHexDigit(pair[1]);
        }
    }

    void Spin(int_fast32_t n) noexcept {
        while (--n != 0) {
            NOP;
        }
    }

    void WarmCache(char *password, const std::string_view& hash, int_fast32_t n) noexcept {
        while (--n != 0) {
            Decrypt(password, hash);
        }
    }

    void Decrypt(char *password, const std::string_view& hash) noexcept {
        auto c = hash.substr(2, 22).data();
        auto i = hash.length() / 2 - 2;
        auto k = Xlat + ParseDecPair(hash.data());

        for (;;) {
            *password++ = *k++ ^ ParseHexPair(c);

            if (i-- == 0) {
                break;
            }

            c += 2;
        }
    }
}
