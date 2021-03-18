/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

#include <cstddef>
#include <type_traits>

namespace swiper {
    namespace {
        ALWAYS_INLINE size_t ParseDecDigit(size_t v) noexcept {
            return v - 48;
        }

        ALWAYS_INLINE uint8_t ParseHexDigit(uint8_t v) noexcept {
            if (v & 64) {
                return v - 87;
            }

            return v - 48;
        }

        ALWAYS_INLINE size_t ParseDecPair(const std::string_view& pair) noexcept {
            return ParseDecDigit(size_t(pair[0])) * 10 + ParseDecDigit(size_t(pair[1]));
        }

        ALWAYS_INLINE uint8_t ParseHexPair(const std::string_view& pair, size_t offset) noexcept {
            return ParseHexDigit(uint8_t(pair[offset])) * 16 + ParseHexDigit(uint8_t(pair[offset + 1]));
        }
    }

    void Spin(int32_t n) noexcept {
        while (--n != 0) {
            NOP;
        }
    }

    void WarmCache(char *password, const std::string_view& hash, int32_t n) noexcept {
        while (--n != 0) {
            Decrypt(password, hash);
        }
    }

    void Decrypt(char *password, const std::string_view& hash) noexcept {
        auto j = hash.length() - 2;
        auto i = j / 2 - 1;
        auto k = Xlat + ParseDecPair(hash) + i;
        auto p = password + i;

        for (;;) {
            *p-- = *k-- ^ ParseHexPair(hash, j);

            if (i-- == 0) {
                break;
            }

            j -= 2;
        }
    }
}
