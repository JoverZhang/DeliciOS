// SPDX-License-Identifier: GPL-2.0-only

#pragma once

/*
 * Optional: not supported by clang
 *
 *   gcc: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-externally_005fvisible-function-attribute
 */
#if __has_attribute(__externally_visible__)
# define __visible                      __attribute__((__externally_visible__))
#else
# define __visible                      __attribute__((visibility("default")))
#endif

#define public        __visible

#define noreturn      __attribute__ ((noreturn))

#define likely(x)     __builtin_expect(!!(x), 1)
#define unlikely(x)   __builtin_expect(!!(x), 0)
