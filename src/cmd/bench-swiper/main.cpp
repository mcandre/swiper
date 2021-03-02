/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cstring>
#include <random>

#include "swiper/swiper.hpp"

static void gen_password(char *password, unsigned int prng_seed) {
    std::uniform_int_distribution distribution(0, 127);
    std::default_random_engine rng(prng_seed);

    for (auto i = 10; i >= 0; i--) {
        password[i] = uint8_t(distribution(rng));
    }
}

int main() {
    const auto prng_seed = (unsigned int)(time(nullptr));
    char password[12];
    gen_password(password, prng_seed);
    char hash[25];
    memset(hash, 0, sizeof(hash));
    swiper::Encrypt(hash, prng_seed, password);
    hash[2 * (1 + strlen(password))] = '\0';

    for (auto i = 1000000000u; i > 0u; i--) {
        swiper::Decrypt(password, hash);
    }

    return EXIT_SUCCESS;
}
