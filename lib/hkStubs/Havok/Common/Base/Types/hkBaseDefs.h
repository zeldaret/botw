#pragma once

#define HK_FORCE_INLINE inline __attribute__((always_inline))
#define HK_ALWAYS_INLINE HK_FORCE_INLINE
#define HK_NEVER_INLINE __attribute__((noinline))

#define HK_VISIBILITY_HIDDEN __attribute__((visibility("hidden")))

#define HK_RESTRICT __restrict

#define HK_MAX_NUM_THREADS 12

#define HK_NEXT_MULTIPLE_OF(ALIGNMENT, VALUE)                                                      \
    (((VALUE) + ((ALIGNMENT)-1)) & (~((ALIGNMENT) + (VALUE)*0 - 1)))
