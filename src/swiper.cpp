/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

namespace swiper {
    namespace {
        /**
         * @brief ParseDecDigit reads a decimal character.
         *
         * @param v ASCII character
         *
         * @returns numerical value
         */
        template<class T>
        auto ParseDecDigit(T v) {
            return v - 48;
        }

        /**
         * @brief ParseDecPair reads decimal text.
         *
         * @param pair 2 ASCII characters
         *
         * @returns numerical value
         */
        template<class T>
        auto ParseDecPair(const T* pair) noexcept {
            return 10 * ParseDecDigit(pair[0]) + ParseDecDigit(pair[1]);
        }

        /**
         * @brief ParseHexDigit reads a hexadecimal character.
         *
         * @param v ASCII character
         *
         * @returns numerical value
         */
        template<class T>
        auto ParseHexDigit(T v) noexcept {
            return v - (v & 64 ? 55 : 48);
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
            return 16 * ParseHexDigit(pair[0]) + ParseHexDigit(pair[1]);
        }

        /**
         * @brief Xlat is a fixed XOR key.
         */
        constexpr char Xlat[32] = {
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

    void Decrypt(char* password, size_t hash_len, const char* hash) noexcept {
        auto i = hash_len / 2 - 2;
        auto k = Xlat + ParseDecPair(hash);
        auto c = hash + 2;

        for (;;) {
            *password++ = static_cast<char>(*k++ ^ ParseHexPair(c));

            if (i-- == 0) {
                return;
            }

            c += 2;
        }
    }
}
