#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resResourceASSetting.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// FIXME: very incomplete
class ASSetting {
    SEAD_SINGLETON_DISPOSER(ASSetting)
    ASSetting() = default;
    virtual ~ASSetting();

public:
    void init(const sead::SafeString& config_path, sead::Heap* heap);
    res::ASParamParser* getBoneParams(const sead::SafeString& key) const;

private:
    res::Handle mHandle;
};
KSYS_CHECK_SIZE_NX150(ASSetting, 0x78);

}  // namespace ksys::act
