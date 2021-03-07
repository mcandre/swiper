/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <chrono>
#include <cstring>
#include <ctime>
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
    char password[12];
    memset(password, 0, sizeof(password));
    swiper::WarmCache(password, hash, 100);
    const auto hashes = 1000000000;
    const auto start = std::chrono::high_resolution_clock::now();
    swiper::WarmCache(password, hash, hashes);
    const auto end = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    const auto rate = 1000.0 * hashes / ms;
    std::cout << std::scientific << rate << " hash/sec" << std::endl;
    return EXIT_SUCCESS;
}
