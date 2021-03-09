/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
#include <chrono>
#include <cstring>
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
    const auto hashes = int32_t(1000000000);
    const auto start = std::chrono::high_resolution_clock::now();
    swiper::WarmCache(password, hash, hashes);
    const auto end = std::chrono::high_resolution_clock::now();
    assert(strcmp(password, "monke") == 0);
    const auto elapsed = end - start;
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    const auto bandwidth = 1000.0 * hashes / ms;
    const auto latency = ns / hashes;
    std::cout << std::scientific;
    std::cout << bandwidth << " hash/sec" << std::endl;
    std::cout << latency << " ns/call" << std::endl;
    return EXIT_SUCCESS;
}
