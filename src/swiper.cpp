/**
 * @copyright 2020 YelloSoft
*/

#include "swiper/swiper.hpp"

#include <type_traits>

namespace swiper {
    namespace {
        const uint8_t Xlat[32] = {
            0x64, 0x73, 0x66, 0x64,
            0x3b, 0x6b, 0x66, 0x6f,
            0x41, 0x2c, 0x2e, 0x69,
            0x79, 0x65, 0x77, 0x72,
            0x6b, 0x6c, 0x64, 0x4a,
            0x4b, 0x44, 0x48, 0x53,
            0x55, 0x42, 0x73, 0x00,
            0x00, 0x00, 0x00, 0x00
        };

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

        template <class T>
        uint8_t FormatDigit(T t) noexcept {
            if (t > T(9)) {
                return  uint8_t(t) + '\x57';
            }

            return uint8_t(t) + '\x30';
        }

        // Warning: Omits null terminator, to be placed at buf[2].
        template <class T>
        void FormatPair(std::string& result, size_t offset, T value, T base) noexcept {
            T remainder = value % base;
            result[offset] = FormatDigit((value - remainder) / base);
            result[offset + 1]= FormatDigit(remainder);
        }
    }

    void Encrypt(std::string& hash, size_t seed, const std::string& password) noexcept {
        auto len = password.length();

        if (len > size_t(11)) {
            len = size_t(11);
        }

        FormatPair(hash, 0, seed, size_t(10));
        auto xlat_seeded = Xlat + seed;

        for (auto i = size_t(0), j = size_t(2); i < len; i++, j += 2) {
            const auto c = uint8_t(password[i] ^ xlat_seeded[i]);
            FormatPair(hash, j, c, uint8_t(16));
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
