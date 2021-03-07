/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <chrono>
#include <cstring>
#include <ctime>
#include <iostream>
#include <random>

#include "swiper/swiper.hpp"

static void gen_password(char *password, unsigned int prng_seed) {
    std::uniform_int_distribution distribution_ascii(0, 127);
    std::default_random_engine rng(prng_seed);
    const auto est_len = 5;

    for (auto i = est_len - 1; i != -1; i--) {
        password[i] = uint8_t(distribution_ascii(rng));
    }
}

int main() {
    const auto prng_seed = (unsigned int)(time(nullptr));
    const auto hs_len = 16;
    char hs[hs_len][13];
    memset(hs, 0, sizeof(hs));
    char password[12];
    memset(password, 0, sizeof(password));
    gen_password(password, prng_seed);

    for (auto i = hs_len - 1; i != -1; i--) {
         swiper::Encrypt(hs[i], i, password);
    }

    const auto hashes = 1000000000;
    const auto start = std::chrono::high_resolution_clock::now();

    for (auto i = hashes, j = 0; i != 0; i--, j++) {
        swiper::Decrypt(password, hs[j]);

        if (j == hs_len - 1) {
            j = 0;
        }
    }

    const auto end = std::chrono::high_resolution_clock::now();
    const auto sec = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
    const auto rate = double(hashes)/sec;
    std::cout << std::scientific << rate << " hash/sec" << std::endl;

    return EXIT_SUCCESS;
}
