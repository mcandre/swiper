/**
 * @copyright 2021 YelloSoft
 */

#include "main.hpp"

#include <cassert>
#include <string>
using namespace std::string_literals;

#include "swiper/swiper.hpp"

int main() {
    const auto hashes = {
        "00091c080f5e"s,
        "011e090a500e"s,
        "020b0b550003"s,
        "030954050d0a"s,
        "045604080424"s,
        "050609012a49"s,
        "060b002f474b"s,
        "07022e42450c"s,
        "082c4340021c"s,
        "094141071200"s,
        "104306170e12"s,
        "1104160b1c17"s,
        "12140a19190e"s,
        "1308181c0009"s,
        "141a1d050701"s,
        "151f04020f2f"s
    };

    for (const auto& h : hashes) {
        auto password = std::string(h.length() / 2 - 1, '0');
        swiper::Decrypt(password, h);
        assert(password == "monke"s);
    }
}
