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

void warm_cache(char password[12], char hs[16][13], int hs_len, int iterations) {
    for (auto i = iterations, j = 0; i != 0; i--, j++) {
        swiper::Decrypt(password, hs[j]);

        if (j == hs_len - 1) {
            j = 0;
        }
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
    char hs[16][13];
    const auto hs_len = int(sizeof(hs)/13);
    memset(hs, 0, sizeof(hs));
    char password[12];
    memset(password, 0, sizeof(password));
    gen_password(password, prng_seed);

    for (auto i = hs_len - 1; i != -1; i--) {
         swiper::Encrypt(hs[i], i, password);
    }

    warm_cache(password, hs, hs_len, 100);
    const auto hashes = 1000000000;
    const auto start = std::chrono::high_resolution_clock::now();
    warm_cache(password, hs, hs_len, hashes);
    const auto end = std::chrono::high_resolution_clock::now();
    const auto sec = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
    const auto rate = double(hashes)/sec;
    std::cout << std::scientific << rate << " hash/sec" << std::endl;
    return EXIT_SUCCESS;
}
