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
 * @param argv CLI arguments
 *
 * @returns CLI exit code
 */
int main(int argc, const char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <type 7 hash>" << std::endl;
    }

    const auto *hash_signed = argv[1];
    const auto hash_len = strlen(hash_signed);
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
