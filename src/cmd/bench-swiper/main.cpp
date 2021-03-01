/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <charconv>
#include <chrono>
#ifdef _WIN32
#define _CRT_RAND_S
#include <cstdlib>
#endif
#include <iostream>
#include <random>
#include <string>
#include <thread>

#include "swiper/swiper.hpp"

static std::string gen_password(unsigned int prng_seed) {
    std::string s;

    std::uniform_int_distribution distribution(0, 127);
    std::default_random_engine rng(prng_seed);

    for (size_t i = 0; i < 11; i++) {
        auto p = char(distribution(rng));
        s += p;
    }

    return s;
}

int main(int argc, const char **argv) {
    unsigned int max_time_sec = 2;

    const auto args = std::vector<std::string_view>{argv, argv+argc};

    if (args.size() == 2) {
        unsigned int m_t_s = 0;
        auto sv = args.at(1);
        auto result = std::from_chars(sv.data(), sv.data() + sv.size(), m_t_s);

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

    auto prng_seed = (unsigned int)(time(nullptr));
    const auto password = gen_password(prng_seed);
    const auto hash = swiper::Encrypt(prng_seed, password);

    volatile unsigned long long successes = 0;
    volatile time_t start = time(nullptr);
    std::thread t([&]() {
        std::this_thread::sleep_for(std::chrono::seconds(max_time_sec));
        auto elapsed = time(nullptr) - start;
        std::cout << std::scientific;
        std::cout << double(successes)/elapsed << " hashes/sec" << std::endl;
        exit(EXIT_SUCCESS);
    });

    for (;;) {
        (void) swiper::Decrypt(hash);
        successes++;
    }
}
