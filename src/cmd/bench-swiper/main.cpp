/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <chrono>
#include <cstring>
#include <ctime>
#include <iostream>
#include <random>

#if defined(_WIN32)
#include <Windows.h>
#elif defined(__linux__)
#include <sched.h>
#include <sys/sysinfo.h>
#endif

#include "swiper/swiper.hpp"

static void gen_password(char *password, unsigned int prng_seed) {
    std::uniform_int_distribution distribution_ascii(0, 127);
    std::default_random_engine rng(prng_seed);
    const auto est_len = 5;

    for (auto i = est_len - 1; i != -1; i--) {
        password[i] = uint8_t(distribution_ascii(rng));
    }
}

void warm_cache(char *password, char *hash, int iterations) {
    for (auto i = iterations; i != 0; i--) {
        swiper::Decrypt(password, hash);
    }
}

int main() {
    #if defined(_WIN32)
    ::SetProcessAffinityMask(GetCurrentProcess(), 0x00);
    #elif defined(__linux__)
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
    #endif

    const auto prng_seed = (unsigned int)(time(nullptr));
    char hash[13];
    memset(hash, 0, sizeof(hash));
    char password[12];
    memset(password, 0, sizeof(password));
    gen_password(password, prng_seed);
    swiper::Encrypt(hash, 7, password);
    warm_cache(password, hash, 100);
    const auto hashes = 1000000000;
    const auto start = std::chrono::high_resolution_clock::now();
    warm_cache(password, hash, hashes);
    const auto end = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    const auto rate = 1000.0 * hashes / ms;
    std::cout << std::scientific << rate << " hash/sec" << std::endl;
    return EXIT_SUCCESS;
}
