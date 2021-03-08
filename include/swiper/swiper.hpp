#pragma once

/**
 * @copyright 2021 YelloSoft
 * @mainpage
 *
 * @ref swiper breaks Cisco IOSv7 passwords.
 */

/**
 * @brief swiper manages legacy Cisco passwords.
 */
namespace swiper {
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
    void Encrypt(char *hash, short int seed, const char *password) noexcept;

    /**
     * @brief WarmCache accelerates successive @ref Decrypt calls,
     * by prepopulating the system cache.
     *
     * @param password max 11 characters + null terminator
     * @param hash Cisco IOSv7
     * @param n iterations (non-negative)
     */
    void WarmCache(char *password, const char *hash, int n) noexcept;

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
