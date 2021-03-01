/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <charconv>
#include <csignal>
#include <iostream>
#include <string>
#include <unistd.h>

#include "swiper/swiper.hpp"

static std::string gen_password(uint *prng_seed) {
    std::string s;

    for (size_t i = 0; i < 11; i++) {
        auto p = char(rand_r(prng_seed) % 128);
        s += p;
    }

    return s;
}

volatile unsigned long long successes = 0;
volatile time_t start = 0;
volatile time_t end = 0;

void handle_alarm(int sig) {
    if (sig == SIGALRM) {
        if (end == 0) {
            end = time(nullptr);
        }

        auto elapsed = end - start;
        std::cout << double(successes)/elapsed << " hashes/sec" << std::endl;
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, const char **argv) {
    auto max_time_sec = 2;

    const auto args = std::vector<std::string_view>{argv, argv+argc};

    if (args.size() == 2) {
        int m_t_s = 0;
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

    auto prng_seed = uint(time(nullptr));

    auto len = 1000;
    std::vector<std::string> hashes;
    hashes.reserve(len);

    std::cout << std::scientific;

    std::cerr << "generating " << double(len) << " hashes" << std::endl;

    for (auto i = 0; i < len; i++) {
        const auto password = gen_password(&prng_seed);
        hashes.push_back(swiper::Encrypt(&prng_seed, password));
    }

    std::cerr << "decrypting" << std::endl;

    start = time(nullptr);
    signal(SIGALRM, &handle_alarm);
    alarm(max_time_sec);

    size_t i = 0;

    for (;;) {
        auto hash = hashes.at(i);
        auto result = swiper::Decrypt(hash);
        successes++;

        if (i == hash.length()) {
            i = 0;
        }
    }
}
