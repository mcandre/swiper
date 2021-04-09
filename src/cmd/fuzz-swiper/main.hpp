#pragma once

/**
 * @copyright 2021 YelloSoft
 */

#ifdef __SANITIZE_ADDRESS__
#include <stddef.h>
#include <stdint.h>

/**
 * @brief LLVMFuzzerTestOneInput is the entrypoint.
 *
 * @param Data arbitrary input block
 * @param Size block element count
 *
 * @returns 0. Aborts on error.
 */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size);
#endif
