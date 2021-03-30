/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#if defined(_WIN32)
#include <Windows.h>
#elif defined(__linux__)
#include <sched.h>
#include <sys/sysinfo.h>
#endif

#include "swiper/swiper.hpp"

int main() {
    #if defined(_WIN32)
    ::SetProcessAffinityMask(GetCurrentProcess(), 0x00);
    #elif defined(__linux__)
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
    #endif

    const auto hash __attribute__((aligned (16))) = "00091c080f5e\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    char password[16] __attribute__((aligned (16)));
    constexpr auto trials = uint_fast32_t(1 << 30);
    const auto nop_start = std::chrono::steady_clock::now();
    swiper::Spin(trials);
    const auto nop_end = std::chrono::steady_clock::now();
    swiper::WarmCache(password, hash, trials);
    const auto start = std::chrono::steady_clock::now();
    swiper::WarmCache(password, hash, trials);
    const auto end = std::chrono::steady_clock::now();
    const auto nop_elapsed = nop_end - nop_start;
    const auto elapsed = end - start - nop_elapsed;
    const auto total_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    const auto throughput_sec = 1000000000.0 * trials / total_ns;
    const auto latency_ns = double(total_ns) / trials;
    std::cout << std::setprecision(2);
    std::cout << "latency (ns)\tthroughput (password/sec)" << std::endl <<
        std::fixed << std::setw(12) << std::left << latency_ns << "\t" <<
        std::scientific << throughput_sec << std::endl;
    return EXIT_SUCCESS;
}
