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
     * @brief Encrypt produces Cisco IOS^tm type 7 hashes.
     *
     * Truncates to the first 11 characters.
     *
     * @param hash buffer (2 * (1 + password length) characters)
     * @param seed random seed in [0, 16)
     * @param password plaintext ASCII
     */
    void Encrypt(std::string& hash, size_t seed, const std::string& password) noexcept;

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
