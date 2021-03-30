#pragma once

/**
 * @copyright 2021 YelloSoft
 * @mainpage
 *
 * @ref swiper breaks Cisco IOS^tm type 7 passwords.
 */

#include <cstddef>
#include <cstdint>

/**
 * @brief swiper manages legacy Cisco IOS^tm type 7 passwords.
 */
namespace swiper {
    /**
     * @brief Xlat is a fixed XOR key.
     */
    const char Xlat[32] __attribute__((aligned (16))) = {
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
     * @brief Spin performs n NOP's, useful for reducing benchmark noise.
     *
     * @param n iterations (non-negative)
     */
    void Spin(uint_fast32_t n) noexcept;

    /**
     * @brief WarmCache accelerates successive @ref Decrypt calls,
     * by prepopulating the system cache.
     *
     * Warning: Missing null terminator at password[hash.length() / 2 - 1].
     *
     * @param password out buffer (hash length / 2 characters)
     * @param hash Cisco IOS^tm type 7 (lowercase, min length 4)
     * @param n iterations (non-negative)
     */
    void WarmCache(char* password, const char* hash, uint_fast32_t n) noexcept;

    /**
     * @brief Decrypt reverses Cisco IOS type 7 hashes.
     *
     * Warning: Missing null terminator at password[hash.length() / 2 - 1].
     *
     * @param password out buffer (hash length / 2 characters)
     * @param hash Cisco IOS^tm type 7 (lowercase, min length 4)
     * @returns password
     *
     */
    void Decrypt(char* password, const char* hash) noexcept;
}
