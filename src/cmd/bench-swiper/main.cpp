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
#include <string>
using namespace std::string_view_literals;

#include "swiper/swiper.hpp"

constexpr auto trials = 1 << 30;

int main() {
    #if defined(_WIN32)
    ::SetProcessAffinityMask(GetCurrentProcess(), 0x00);
    #elif defined(__linux__)
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
    #endif

    const auto hash = "07022e42450c"sv;
    char password[12];
    memset(password, 0, sizeof(password));
    const auto nop_start = std::chrono::high_resolution_clock::now();
    swiper::Spin(trials);
    const auto nop_end = std::chrono::high_resolution_clock::now();
    swiper::WarmCache(password, hash, 1000);
    const auto start = std::chrono::high_resolution_clock::now();
    swiper::WarmCache(password, hash, trials);
    const auto end = std::chrono::high_resolution_clock::now();
    assert(password == "monke"sv);
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
