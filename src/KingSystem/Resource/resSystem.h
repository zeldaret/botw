#pragma once

#include <prim/seadSafeString.h>

namespace ksys::res {

// In release builds, the only thing this function does is return 1.
// TODO: figure out what this is used for. Stubbed log function?
bool stubbedLogFunction();

// In release builds, the only thing this function does is return 0.
// TODO: figure out what this is used for. Stubbed log function?
bool returnFalse();

// In release builds, the only thing this function does is return 0.
// TODO: figure out what this is used for. Stubbed log function?
bool returnFalse2(const sead::SafeString&);

}  // namespace ksys::res
