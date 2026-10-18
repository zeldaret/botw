#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace ksys::act {

u32 calcAwarenessHash(const sead::SafeString& key);

}  // namespace ksys::act
