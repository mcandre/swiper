/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <algorithm>
#include <cassert>
#include <cstring>

#include "swiper/swiper.hpp"

/**
 * @brief main is the entrypoint.
 *
 * Usage: test-swiper
 *
 * @returns CLI exit code
 */
int main() {
    const char hashes_signed[16][13] = {
        "00091C080F5E",
        "011E090A500E",
        "020B0B550003",
        "030954050D0A",
        "045604080424",
        "050609012A49",
        "060B002F474B",
        "07022E42450C",
        "082C4340021C",
        "094141071200",
        "104306170E12",
        "1104160B1C17",
        "12140A19190E",
        "1308181C0009",
        "141A1D050701",
        "151F04020F2F"
    };

    uint8_t hash[13];
    uint8_t password[12];
    char password_signed[12];

    for (const auto* hash_signed : hashes_signed) {
        const auto hash_len = strlen(hash_signed);
        std::copy(hash_signed, hash_signed + hash_len + 1, hash);
        swiper::Decrypt(password, hash_len, hash);
        const auto password_len = hash_len / 2 - 1;
        password[password_len] = '\0';
        std::copy(password, password + password_len + 1, password_signed);
        assert(strcmp(password_signed, "monke") == 0);
    }
}
