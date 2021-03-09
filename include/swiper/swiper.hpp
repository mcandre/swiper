#pragma once

/**
 * @copyright 2021 YelloSoft
 * @mainpage
 *
 * @ref swiper breaks Cisco IOSv7 passwords.
 */

#include <cstdint>

/**
 * @brief swiper manages legacy Cisco passwords.
 */
namespace swiper {
    /**
     * @brief ParseDigit reads a decimal or hexadecimal character as a number.
     * 
     * @param c printed representation
     * @returns value
     */
    int32_t ParseDigit(char c);

    /**
     * @brief ParseDec reads a decimal string as a number.
     * 
     * @param pair 2 characters
     * @returns value
     */
    int32_t ParseDec(const char *pair);

    /**
     * @brief ParseHex reads a hexadecimal string as a number.
     * 
     * @param pair 2 characters
     * @returns value
     */
    int32_t ParseHex(const char *pair);

    /**
     * @brief Encrypt produces Cisco IOSv7 hashes.
     * 
     * Truncates to the first 11 characters.
     * 
     * Warning: Omits null terminator, to be placed at hash[2 * (1 + strlen(password))].
     *
     * @param hash max 24 characters + null terminator
     * @param seed random seed in [0, 16)
     * @param password plaintext ASCII
     */
    void Encrypt(char *hash, int32_t seed, const char *password) noexcept;

    /**
     * @brief WarmCache accelerates successive @ref Decrypt calls,
     * by prepopulating the system cache.
     *
     * @param password max 11 characters + null terminator
     * @param hash Cisco IOSv7
     * @param n iterations (non-negative)
     */
    void WarmCache(char *password, const char *hash, int32_t n) noexcept;

    /**
     * @brief Decrypt reverses Cisco IOSv7 hashes.
     *
     * Hexadecimal data is lowercase.
     *
     * Warning: Omits null terminator, to be placed at password[strlen(hash)/2 - 1].
     *
     * @param password max 11 characters + null terminator
     * @param hash Cisco IOSv7 (lowercase)
     *
     */
    void Decrypt(char *password, const char *hash) noexcept;
}
