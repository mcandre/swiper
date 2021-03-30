/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
#include <cstring>



#include <iostream>

#include "swiper/swiper.hpp"

int main() {
    const char hashes[16][34] __attribute__((aligned (16))) = {
        "00091c080f5e",
        "011e090a500e",
        "020b0b550003",
        "030954050d0a",
        "045604080424",
        "050609012a49",
        "060b002f474b",
        "07022e42450c",
        "082c4340021c",
        "094141071200",
        "104306170e12",
        "1104160b1c17",
        "12140a19190e",
        "1308181c0009",
        "141a1d050701",
        "151f04020f2f"
    };

    char password[16] __attribute__((aligned (16)));

    for (auto i = 0; i < 16; i++) {
        const auto hash = hashes[i];
        swiper::Decrypt(password, hash);
        password[strlen(hash) / 2 - 1] = '\0';



        std::cerr << "Hash: " << hash << std::endl;
        std::cerr << "Password: " << password << std::endl;

        assert(strcmp(password, "monke") == 0);
    }
}
