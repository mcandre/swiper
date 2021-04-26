/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#if defined(_WIN32)
#include <Windows.h>
#elif defined(__linux__)
#include <sched.h>
#include <sys/sysinfo.h>
#endif

#include <benchmark/benchmark.h>

#include "swiper/swiper.hpp"

/**
 * @brief BM_Decrypt measures @ref swiper::Decrypt performance.
 *
 * @param state contains a Cisco hash
 */
static void BM_Decrypt(
    benchmark::State& state, // NOLINT(google-runtime-references)
    const char* hash_signed
) {
    auto hash_len = strlen(hash_signed);
    uint8_t hash[25];
    std::copy(hash_signed, hash_signed + hash_len, hash);
    uint8_t password[12];

    for (auto _ : state) { // NOLINT(clang-analyzer-deadcode.DeadStores)
        swiper::Decrypt(password, hash_len, hash);
        benchmark::DoNotOptimize(password);
    }
}

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
int main(int argc, char** argv) {
    const auto* hash_signed = argv[1];
    benchmark::RegisterBenchmark("Decrypt", BM_Decrypt, hash_signed);
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    return EXIT_SUCCESS;
}
