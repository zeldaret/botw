#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Ecosystem/ecoSystem.h"

namespace uking {

// Interfaces to original bodies. These declarations add no implementations.
const ksys::eco::AreaItem* sub_7100657D2C(ksys::eco::AreaItemSet* items,
                                          const sead::Vector3f& position,
                                          const sead::SafeString& name);
s32 sub_7100657EC4(const ksys::eco::AreaItem* item, s32 equipment_category);
f32 getActorTraverseDist(f32 scale, const sead::SafeString& name);
f32 getActorTraverseDistPlus100(f32 scale, const sead::SafeString& name);

}  // namespace uking
