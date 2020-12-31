#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

/// Current Resource Name Manager?
/// Stubbed in release builds.
class CurrentResNameMgr {
    SEAD_SINGLETON_DISPOSER(CurrentResNameMgr)
    CurrentResNameMgr() = default;

public:
    void init(sead::Heap* heap);
    sead::SafeString getCurrentResName() const;
};
KSYS_CHECK_SIZE_NX150(CurrentResNameMgr, 0x20);

}  // namespace ksys::res
