/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

#include <cstring>

namespace swiper {
    namespace {
        inline auto ParseDecPair(const char* pair) noexcept {
            return static_cast<size_t>(pair[0] & 1 ? pair[1] - 38 : pair[1] - 48);
        }

        inline auto ParseHexDigit(char v) noexcept {
            return v & 64 ? v - 87 : v - 48;
        }

        // inline auto ParseHexPair(const char* pair) noexcept {
        //     return 16 * ParseHexDigit(pair[0]) + ParseHexDigit(pair[1]);
        // }
    }

    void Spin(volatile uint_fast32_t n) noexcept {
        while (n-- != 0) {}
    }

    void WarmCache(char* password, const char* hash, volatile uint_fast32_t n) noexcept {
        while (n-- != 0) {
            Decrypt(password, hash);
        }
    }

    void Decrypt(char* password, const char* hash) noexcept {
        const auto key = Xlat + ParseDecPair(hash);

        for (auto i = static_cast<size_t>(0); i < static_cast<size_t>(16); i++) {
            password[i] = ParseHexDigit(hash[i * 2 + 2]);
        }

        #pragma clang loop vectorize(enable) interleave(enable)
        for (auto i = static_cast<size_t>(0); i < static_cast<size_t>(16); i++) {
            password[i] *= 16;
        }

        for (auto i = static_cast<size_t>(0); i < static_cast<size_t>(16); i++) {
            password[i] += ParseHexDigit(hash[i * 2 + 3]);
        }

        #pragma clang loop vectorize(enable) interleave(enable)
        for (auto i = static_cast<size_t>(0); i < static_cast<size_t>(16); i++) {
            password[i] ^= key[i];
        }
    }
}
