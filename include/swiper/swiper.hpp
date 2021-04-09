#pragma once

/**
 * @copyright 2021 YelloSoft
 * @mainpage
 *
 * @ref swiper breaks Cisco type 7 passwords.
 */

#include <cstddef>
#include <cstdint>

/**
 * @brief swiper manages legacy Cisco type 7 passwords.
 */
namespace swiper {
    /**
     * @brief Xlat is a fixed XOR key.
     */
    const char Xlat[32] = {
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
     * @brief Decrypt reverses Cisco type 7 hashes.
     *
     * @param password out buffer, min hash_len / 2 - 2 characters, non-null terminated
     * @param hash_len string length of hash
     * @param hash Cisco Itype 7 hash, uppercase, min length 4
     *
     */
    void Decrypt(char* password, size_t hash_len, const char* hash) noexcept;
}
