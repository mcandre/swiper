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

        ALWAYS_INLINE size_t ParseDecPair(const std::string& pair, size_t offset) noexcept {
            return ParseDecDigit(size_t(pair[offset])) * 10 + ParseDecDigit(size_t(pair[offset + 1]));
        }

        ALWAYS_INLINE uint8_t ParseHexPair(const std::string& pair, size_t offset) noexcept {
            return ParseHexDigit(uint8_t(pair[offset])) * 16 + ParseHexDigit(uint8_t(pair[offset + 1]));
        }
    }

    void Spin(int32_t n) noexcept {
        while (--n != 0) {
            __asm("");
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
                break;
            }
        }
    }
}
