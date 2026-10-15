#pragma once
#include <prim/seadRuntimeTypeInfo.h>

namespace ksys::act {

// Inferred name for the original guarded type-info getter at 0x2365c.
// The original getter does not read its receiver. No new type-info object is created.
const sead::RuntimeTypeInfo::Interface* getRoadNpcRuntimeTypeInfo();

}  // namespace ksys::act
