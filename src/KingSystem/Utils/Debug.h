#pragma once

#include <prim/seadSafeString.h>

namespace ksys::util {

inline void PrintDebug([[maybe_unused]] const sead::SafeString& message) {}

template <typename... Args>
inline void PrintDebugFmt(const char* format, const Args&...) {}

}  // namespace ksys::util
