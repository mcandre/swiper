/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

#include <type_traits>

namespace swiper {
    namespace {
        ALWAYS_INLINE auto ParseDecDigit(char v) noexcept {
            return v - 48;
        }

        ALWAYS_INLINE auto ParseHexDigit(char v) noexcept {
            if (v & 64) {
                return v - 87;
            }

            return v - 48;
        }

        ALWAYS_INLINE auto ParseDecPair(const std::string_view& pair) noexcept {
            return ParseDecDigit(pair[0]) * 10 + ParseDecDigit(pair[1]);
        }

        ALWAYS_INLINE auto ParseHexPair(const char *pair) noexcept {
            return ParseHexDigit(pair[0]) * 16 + ParseHexDigit(pair[1]);
        }
    }

    void Spin(int n) noexcept {
        while (--n != 0) {
            NOP;
        }
    }

    void WarmCache(char *password, const std::string_view& hash, int n) noexcept {
        while (--n != 0) {
            Decrypt(password, hash);
        }
    }

    void Decrypt(char *password, const std::string_view& hash) noexcept {
        auto i = hash.length() / 2 - 2;
        auto c = hash.data();
        auto k = Xlat + ParseDecPair(hash);

        for (;;) {
            c += 2;
            *password++ = *k++ ^ ParseHexPair(c);

            if (i-- == 0) {
                break;
            }
        }
    }
}
