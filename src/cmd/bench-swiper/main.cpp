/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cstring>
#include <ctime>
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
    const auto hashes_len = 16;
    char hashes[hashes_len][13];
    memset(hashes, 0, sizeof(hashes));
    char password[12];

    for (auto i = hashes_len - 1; i != -1; i--) {
        memset(password, 0, sizeof(password));
        gen_password(password, prng_seed);
        swiper::Encrypt(hashes[i], i, password);
    }

    for (auto i = 1000000000, j = 0; i != 0; i--, j++) {
        swiper::Decrypt(password, hashes[j]);

        if (j == hashes_len - 1) {
            j = 0;
        }
    }

    return EXIT_SUCCESS;
}
