/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include "swiper/swiper.hpp"

/**
 * @brief main is the entrypoint.
 *
 * Usage: bench-swiper <Cisco type 7 hash>
 *
 * @param argc argument count
 * @param argv CLI arguments (min length 2, including the program name)
 *
 * @returns CLI exit code
 */
int main(int /* argc */, const char **argv) {
    const char *hash_signed{ argv[1] };
    const size_t hash_len{ strlen(hash_signed) };
    uint8_t hash[25];
    std::copy(hash_signed, hash_signed + hash_len, hash);
    uint8_t password[12];

    ankerl::nanobench::Bench()
        .minEpochIterations(1UL << 24UL)
        .run("crack", [&] {
            swiper::Decrypt(password, hash_len, hash);
            ankerl::nanobench::doNotOptimizeAway(password);
        });

    return EXIT_SUCCESS;
}
