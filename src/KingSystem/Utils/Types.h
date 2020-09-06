#pragma once

#include <type_traits>

#ifdef SEAD_DEBUG
#define KSYS_CHECK_SIZE_NX150(CLASS, SIZE)
#else
#define KSYS_CHECK_SIZE_NX150(CLASS, SIZE) static_assert(sizeof(CLASS) == SIZE)
#endif
