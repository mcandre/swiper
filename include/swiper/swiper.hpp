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
     * @brief Decrypt reverses Cisco type 7 hashes.
     *
     * @param password out buffer, min hash_len / 2 - 2 characters, non-null terminated
     * @param hash_len string length of hash
     * @param hash Cisco Itype 7 hash, uppercase, min length 4
     *
     */
    void Decrypt(uint8_t* password, size_t hash_len, const uint8_t* hash) noexcept;
}
