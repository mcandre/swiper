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
template<class T>
auto ParseDecPair(const T* pair) noexcept {
    return 10 * pair[0] + pair[1] - 528;
}

/**
 * @brief ParseHexPair reads hexadecimal text.
 *
 * @param pair 2 ASCII characters
 *
 * @returns numerical value
 */
template<class T>
auto ParseHexPair(const T* pair) noexcept {
    return 16 * (pair[0] + (pair[0] & 64 ? 9 : 0)) +
        pair[1] - (pair[1] & 64 ? 55 : 48);
}

/**
 * @brief Xlat is a fixed XOR key.
 */
constexpr char Xlat[27] __attribute__((aligned (16))) = {
    0x64, 0x73, 0x66, 0x64,
    0x3b, 0x6b, 0x66, 0x6f,
    0x41, 0x2c, 0x2e, 0x69,
    0x79, 0x65, 0x77, 0x72,
    0x6b, 0x6c, 0x64, 0x4a,
    0x4b, 0x44, 0x48, 0x53,
    0x55, 0x42, 0x73
};
}

void Decrypt(char* password, size_t hash_len, const char* hash) noexcept {
    auto k = Xlat + ParseDecPair(hash);
    hash += 2;

    for (hash_len = hash_len / 2 - 2;;) {
        *password++ = static_cast<char>(*k++ ^ ParseHexPair(hash));

        if (hash_len-- == 0) {
            return;
        }

        hash += 2;
    }
}
}
