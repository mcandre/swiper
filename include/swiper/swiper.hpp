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
     * @param hash max 24 characters + null terminator
     * @param prng_seed PRNG seed
     * @param password plaintext
     */
    void Encrypt(char *hash, unsigned int prng_seed, const char *password);

    /**
     * @brief Decrypt reverses Cisco IOSv7 hashes.
     *
     * @param password max 11 characters + null terminator
     * @param hash Cisco IOSv7
     *
     */
    void Decrypt(char *password, const char *hash);
}
