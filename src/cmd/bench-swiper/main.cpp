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
static void BM_Decrypt(benchmark::State& state) {
    const auto* hash_signed = state.range(0);
    auto hash_len = strlen(hash_signed);
    unsigned char hash[25];
    std::copy(hash_signed, hash_signed + hash_len, hash);
    unsigned char password[12];

    for (auto _ : state) {
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
int main(int argc, const char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <hash>" << std::endl;
        return EXIT_FAILURE;
    }

    const auto* hash_signed = argv[1];

    BENCHMARK(BM_Decrypt)->Args({hash_signed});
    return EXIT_SUCCESS;
}
