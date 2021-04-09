/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

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

#include "swiper/swiper.hpp"

static void spin(volatile uint_fast32_t n) noexcept {
    while (n-- != 0) {}
}

static void warm_cache(char* password, size_t hash_len, const char* hash, volatile uint_fast32_t n) noexcept {
    while (n-- != 0) {
        swiper::Decrypt(password, hash_len, hash);
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
int main(int argc __attribute__((unused)), const char** argv) {
    #if defined(_WIN32)
    ::SetProcessAffinityMask(GetCurrentProcess(), 0x00);
    #elif defined(__linux__)
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
    #endif

    const auto hash = argv[1];
    auto hash_len = strlen(hash);
    char password[12];
    constexpr auto trials = uint_fast32_t(1 << 30);
    const auto nop_start = std::chrono::steady_clock::now();
    spin(trials);
    const auto nop_end = std::chrono::steady_clock::now();
    warm_cache(password, hash_len, hash, trials);
    const auto start = std::chrono::steady_clock::now();
    warm_cache(password, hash_len, hash, trials);
    const auto end = std::chrono::steady_clock::now();
    const auto nop_elapsed = nop_end - nop_start;
    const auto elapsed = end - start - nop_elapsed;
    const auto total_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    const auto throughput_sec = 1000000000.0 * trials / total_ns;
    const auto latency_ns = double(total_ns) / trials;
    password[hash_len / 2 - 1] = '\0';
    std::cout << password << std::endl;
    std::cerr << std::setprecision(2);
    std::cerr << "latency (ns)\tthroughput (password/sec)" << std::endl <<
        std::fixed << std::setw(12) << std::left << latency_ns << "\t" <<
        std::scientific << throughput_sec << std::endl;
    return EXIT_SUCCESS;
}
