/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
#include <cstring>

#include "swiper/swiper.hpp"

int main() {
    const char *password = "monkey";
    char password2[12];
    char hash[25];

    for (short int i = 0; i < 16; i++) {
        memset(hash, 0, sizeof(hash));
        memset(password2, 0, sizeof(password2));
        swiper::Encrypt(hash, i, password);
        swiper::Decrypt(password2, hash);
        assert(strcmp(password2, password) == 0);
    }
}
