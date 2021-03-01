#pragma once

/**
 * @copyright 2021 YelloSoft
 */

#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size);
