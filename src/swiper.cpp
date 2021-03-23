/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

namespace swiper {
    namespace {
        ALWAYS_INLINE size_t ParseDecPair(const uint_fast8_t *pair) noexcept {
            return size_t(pair[0] & 1 ? pair[1] - 38 : pair[1] - 48);
        }

        ALWAYS_INLINE uint_fast8_t ParseHexDigit(uint_fast8_t v) noexcept {
            return v & 64 ? v - 87 : v - 48;
        }

        ALWAYS_INLINE uint_fast8_t ParseHexPair(const uint_fast8_t *pair) noexcept {
            return 16 * ParseHexDigit(pair[0]) + ParseHexDigit(pair[1]);
        }
    }

    void Spin(volatile uint_fast32_t n) noexcept {
        while (n-- != 0) {}
    }

    void WarmCache(cord& password, const cord& hash, volatile uint_fast32_t n) noexcept {
        while (n-- != 0) {
            Decrypt(password, hash);
        }
    }

    void Decrypt(cord& password, const cord& hash) noexcept {
        const auto [len, buf] = hash;
        auto i = uint_fast8_t(len) / 2 - 2;
        auto p = password.buf;
        auto k = Xlat + ParseDecPair(buf);
        auto c = buf + 2;

        for (;;) {
            *p++ = *k++ ^ ParseHexPair(c);

            if (i-- == 0) {
                break;
            }

            c += 2;
        }
    }
}
