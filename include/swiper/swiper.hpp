#pragma once

/**
 * @copyright 2021 YelloSoft
 * @mainpage
 *
 * @ref swiper breaks Cisco IOS^tm type 7 passwords.
 */

#include <cstddef>
#include <cstdint>
#include <string>

/**
 * @brief swiper manages legacy Cisco IOS^tm type 7 passwords.
 */
namespace swiper {
    /**
     * @brief Xlat is a fixed XOR key.
     */
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

    /**
     * @brief WarmCache accelerates successive @ref Decrypt calls,
     * by prepopulating the system cache.
     *
     * @param password (hash length / 2 - 1 characters)
     * @param hash Cisco IOS^tm type 7
     * @param n iterations (non-negative)
     */
    void WarmCache(std::string& password, const std::string& hash, int32_t n) noexcept;

    /**
     * @brief Decrypt reverses Cisco IOS type 7 hashes.
     *
     * Hexadecimal data is lowercase.
     *
     * @param password (hash length / 2 - 1 characters)
     * @param hash Cisco IOS^tm type 7 (lowercase)
     * @returns password
     *
     */
    void Decrypt(std::string& password, const std::string& hash) noexcept;
}
