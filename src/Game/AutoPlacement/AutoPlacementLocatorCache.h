#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Utils/Types.h"

namespace uking {

struct CachedActorLocators {
    sead::SafeString actorName;
    ksys::act::InfoData::Locators locators;
    sead::BitFlag<u32> usedModes;
};
KSYS_CHECK_SIZE_NX150(CachedActorLocators, 0xf8);

// The original initializer owns this array and its SafeString lifetimes.
extern sead::SafeArray<CachedActorLocators, 96> gActorLocators;

}  // namespace uking
