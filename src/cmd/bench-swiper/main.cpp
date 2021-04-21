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

#include "swiper/swiper.hpp"

/**
 * @brief spin presents an empty loop for overhead measurement.
 *
 * @param n iterations
 */
static void spin(volatile uint_fast32_t n) noexcept {
    while (n-- != 0) {}
}

/**
 * @brief warm_cache promotes application code to icache.
 *
 * @param password out buffer, min hash_len / 2 characters
 * @param hash_len string length of hash
 * @param hash Cisco type 7, uppercase, min length 4
 * @param n iterations
 */
static void warm_cache(unsigned char* password, size_t hash_len, const unsigned char* hash, volatile uint_fast32_t n) noexcept {
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
int main([[maybe_unused]] int argc, const char** argv) {
    #if defined(_WIN32)
    ::SetProcessAffinityMask(GetCurrentProcess(), 0x00);
    #elif defined(__linux__)
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
    #endif

    const auto* hash_signed = argv[1];
    auto hash_len = static_cast<uint_fast8_t>(strlen(hash_signed));
    unsigned char hash[25];
    std::copy(hash_signed, hash_signed + hash_len, hash);
    unsigned char password[12];
    constexpr auto trials = uint_fast32_t(1UL << 30UL);
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
    const auto password_len = hash_len / 2 - 1;
    password[password_len] = '\0';
    char password_signed[12];
    std::copy(password, password + password_len + 1, password_signed);
    std::cout << password_signed << std::endl;
    std::cerr << std::setprecision(2);
    std::cerr << "latency (ns)\tthroughput (password/sec)" << std::endl <<
        std::fixed << std::setw(12) << std::left << latency_ns << "\t" <<
        std::scientific << throughput_sec << std::endl;
    return EXIT_SUCCESS;
}
