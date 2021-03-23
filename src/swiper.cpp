/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

namespace swiper {
    namespace {
        ALWAYS_INLINE size_t ParseDecPair(const char *pair) noexcept {
            return size_t(pair[0] == '0' ? pair[1] - '\x30' : pair[1] - '\x26');
        }

        ALWAYS_INLINE uint_fast8_t ParseHexDigit(uint_fast8_t v) noexcept {
            return v & uint_fast8_t('\x40') ? v - uint_fast8_t('\x57') : v - uint_fast8_t('\x30');
        }

        ALWAYS_INLINE uint_fast8_t ParseHexPair(const uint_fast8_t *pair) noexcept {
            return uint_fast8_t('\x10') * ParseHexDigit(pair[0]) + ParseHexDigit(pair[1]);
        }
    }

    void Spin(volatile uint_fast32_t n) noexcept {
        while (n-- != 0) {}
    }

    void WarmCache(char *password, const std::string_view& hash, volatile uint_fast32_t n) noexcept {
        while (n-- != 0) {
            Decrypt(password, hash);
        }
    }

    void Decrypt(char *password, const std::string_view& hash) noexcept {
        auto c = (const uint_fast8_t*)(hash.substr(2, 22).data());
        auto i = uint_fast8_t(hash.length()) / 2 - 2;
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
