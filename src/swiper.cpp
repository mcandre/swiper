/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

namespace swiper {
namespace {
/**
 * @brief ParseDecPair reads decimal text.
 *
 * @param pair 2 ASCII characters
 *
 * @returns numerical value
 */
template <class T>
auto ParseDecPair(const T *pair) noexcept {
    return 10 * pair[0] + pair[1] - 528;
}

/**
 * @brief ParseHexPair reads hexadecimal text.
 *
 * @param pair 2 ASCII characters
 *
 * @returns numerical value
 */
template <class T>
T ParseHexPair(const T *pair) noexcept {
    return T(16) * (pair[0] +
                    (pair[0] & T(64) ? T(9) : T(0))) +
           pair[1] -
           (pair[1] & T(64) ? T(55) : T(48));
}

/**
 * @brief Xlat is a fixed XOR key.
 */
constexpr uint8_t Xlat[32] = {
    0x64, 0x73, 0x66, 0x64,
    0x3b, 0x6b, 0x66, 0x6f,
    0x41, 0x2c, 0x2e, 0x69,
    0x79, 0x65, 0x77, 0x72,
    0x6b, 0x6c, 0x64, 0x4a,
    0x4b, 0x44, 0x48, 0x53,
    0x55, 0x42, 0x73, 0x00,
    0x00, 0x00, 0x00, 0x00
};
}

void Decrypt(uint8_t *password, size_t hash_len, const uint8_t *hash) noexcept {
    const auto *k = Xlat + ParseDecPair(hash);
    hash += 2;

    for (hash_len = hash_len / 2 - 2;;) {
        *password++ = uint8_t(*k++ ^ ParseHexPair(hash));

        if (hash_len-- == 0) {
            return;
        }

        hash += 2;
    }
}
}
