/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <atomic>
#include <charconv>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#include "swiper/swiper.hpp"

static void gen_password(char *password, unsigned int prng_seed) {
    std::uniform_int_distribution distribution(0, 127);
    std::default_random_engine rng(prng_seed);

    for (size_t i = 0; i < 11; i++) {
        password[i] = char(distribution(rng));
    }
}

int main(int argc, const char **argv) {
    unsigned int max_time_sec = 2;

    const auto args = std::vector<std::string_view>{argv, argv+argc};

    if (args.size() == 2) {
        unsigned int m_t_s;
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
    swiper::Encrypt(hash, prng_seed, password);
    std::atomic<unsigned long long> successes = 0;
    const time_t start = time(nullptr);

    std::thread t([&]() {
        std::this_thread::sleep_for(std::chrono::seconds(max_time_sec));
        const auto elapsed = time(nullptr) - start;
        std::cout << std::scientific;
        std::cout << double(successes)/elapsed << " hashes/sec" << std::endl;
        exit(EXIT_SUCCESS);
    });

    for (;;) {
        swiper::Decrypt(password, hash);
        successes++;
    }
}
