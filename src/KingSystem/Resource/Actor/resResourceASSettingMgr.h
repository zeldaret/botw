#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/Actor/resResourceASSetting.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

// FIXME: very incomplete
class ASSettingMgr {
    SEAD_SINGLETON_DISPOSER(ASSettingMgr)
    ASSettingMgr() = default;
    virtual ~ASSettingMgr() = default;

public:
    void init(const sead::SafeString& config_path, sead::Heap* heap);
    ASParamParser* getBoneParams(const sead::SafeString& key) const;

private:
    Handle mHandle;
};
KSYS_CHECK_SIZE_NX150(ASSettingMgr, 0x78);

}  // namespace ksys::res
