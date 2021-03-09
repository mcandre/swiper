/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
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

int main() {
    #if defined(_WIN32)
    ::SetProcessAffinityMask(GetCurrentProcess(), 0x00);
    #elif defined(__linux__)
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
    #endif

    const char *hash = "07022e42450c";
    char password[6];
    memset(password, 0, sizeof(password));
    swiper::WarmCache(password, hash, int32_t(100));
    const auto trials = int32_t(1000000000);
    const auto start = std::chrono::high_resolution_clock::now();
    swiper::WarmCache(password, hash, trials);
    const auto end = std::chrono::high_resolution_clock::now();
    assert(strcmp(password, "monke") == 0);
    const auto elapsed = end - start;
    const auto total_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    const auto bandwidth_sec = 1000000000.0 * trials / total_ns;
    const auto latency_ns = double(total_ns) / trials;
    std::cout << std::setprecision(2);
    std::cout << "latency (ns)\tbandwidth (password/sec)" << std::endl <<
        std::fixed << std::setw(12) << std::left << latency_ns << "\t" <<
        std::scientific << bandwidth_sec << std::endl;
    return EXIT_SUCCESS;
}
