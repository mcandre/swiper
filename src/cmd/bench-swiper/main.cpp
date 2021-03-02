/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <charconv>
#include <chrono>
#include <cstring>
#include <iostream>
#include <random>

#include "swiper/swiper.hpp"

static void gen_password(char *password, unsigned int prng_seed) {
    std::uniform_int_distribution distribution(0, 127);
    std::default_random_engine rng(prng_seed);

    for (auto i = 10; i >= 0; i--) {
        password[i] = uint8_t(distribution(rng));
    }
}

int main(int argc, const char **argv) {
    auto max_time_sec = 2;
    const auto args = std::vector<std::string_view>{argv, argv+argc};

    if (args.size() == 2) {
        auto m_t_s = 0;
        const auto sv = args.at(1);
        const auto result = std::from_chars(sv.data(), sv.data() + sv.size(), m_t_s);

        if (result.ec == std::errc::invalid_argument) {
            std::cerr << "error: max time seconds must be an integer" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (m_t_s < 1) {
            std::cerr << "error: max time seconds must be at least 1" << std::endl;
            exit(EXIT_FAILURE);
        }

        max_time_sec = m_t_s;
    }

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
