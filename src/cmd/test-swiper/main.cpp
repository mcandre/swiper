/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
#include <cstring>

#include "swiper/swiper.hpp"

int main() {
    const char hashes[16][13] = {
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

    constexpr auto hash_len = static_cast<size_t>(12);
    char password[12];
    constexpr auto password_len = hash_len / 2 - 1;

    for (auto i = 0; i < 16; i++) {
        const auto hash = hashes[i];
        swiper::Decrypt(password, hash_len, hash);
        password[password_len] = '\0';
        assert(strcmp(password, "monke") == 0);
    }
}
