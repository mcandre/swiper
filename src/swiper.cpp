/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"





#include <iostream>


#include <type_traits>

namespace swiper {
    namespace {
        template <class T>
        typename std::enable_if<std::is_arithmetic<T>::value, T>::type
        ParseDigit(T t) noexcept {
            if (t & T(64)) {
                return t - T(87);
            }

            return t - T(48);
        }

        template <class T>
        typename std::enable_if<std::is_arithmetic<T>::value, T>::type
        ParsePair(const std::string& pair, size_t offset, T base) noexcept {
            return ParseDigit(T(pair[offset])) * base + ParseDigit(T(pair[1 + offset]));
        }
    }

    void WarmCache(std::string& password, const std::string& hash, int32_t n) noexcept {
        while (--n != 0) {
            Decrypt(password, hash);
        }
    }

    void Decrypt(std::string& password, const std::string& hash) noexcept {
        auto j = hash.length() - 2;

        if (j == 0) {
            return;
        }

        auto i = j / 2;
        auto xlat_seeded = Xlat + ParsePair(hash, 0, size_t(10));

        for (;;) {
            --i;
            password[i] = xlat_seeded[i] ^ ParsePair(hash, j, uint8_t(16));
            j -= 2;

            if (i == 0) {
                return;
            }
        }
    }
}
