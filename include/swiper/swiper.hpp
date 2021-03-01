#pragma once

/**
 * @copyright 2021 YelloSoft
 * @mainpage
 *
 * @ref swiper breaks Cisco IOSv7 passwords.
 */

#include <optional>
#include <string>
#ifdef __APPLE__
#include <sys/types.h>
#endif
#include <vector>

/**
 * @brief swiper manages legacy Cisco passwords.
 */
namespace swiper {
    /**
     * @brief Encrypt produces Cisco IOSv7 hashes.
     *
     * @param prng_seed PRNG seed
     * @param password plaintext
     *
     * @returns Cisco IOSv7 hash
     */
    std::string Encrypt(uint *prng_seed, const std::string &password);

    /**
     * @brief Decrypt reverses Cisco IOSv7 hashes.
     *
     * @param hash Cisco IOSv7
     *
     * @returns password
     */
    std::string Decrypt(const std::string &hash);
}
