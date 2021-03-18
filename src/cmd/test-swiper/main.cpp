/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
#include <cstring>
#include <string>
using namespace std::string_view_literals;

#include "swiper/swiper.hpp"

int main() {
    const auto hashes = {
        "00091c080f5e"sv,
        "011e090a500e"sv,
        "020b0b550003"sv,
        "030954050d0a"sv,
        "045604080424"sv,
        "050609012a49"sv,
        "060b002f474b"sv,
        "07022e42450c"sv,
        "082c4340021c"sv,
        "094141071200"sv,
        "104306170e12"sv,
        "1104160b1c17"sv,
        "12140a19190e"sv,
        "1308181c0009"sv,
        "141a1d050701"sv,
        "151f04020f2f"sv
    };

    char password[12];

    for (const auto& h : hashes) {
        memset(password, 0, sizeof(password));
        swiper::Decrypt(password, h);
        assert(password == "monke"sv);
    }
}
