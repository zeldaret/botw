#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class ResourceUnit;

// FIXME: incomplete
class Handle {
    SEAD_RTTI_BASE(Handle)
public:
    enum class Status {
        _0 = 0,
    };

    Handle();
    virtual ~Handle();

    Status getStatus() const;

private:
    enum class Flag : u8 {
        _1 = 0x1,
    };

    sead::TypedBitFlag<Flag> mFlags = Flag::_1;
    Status mStatus = Status::_0;
    ResourceUnit* mUnit = nullptr;
    util::ManagedTaskHandle mTaskHandle;
    void* _40 = nullptr;
    void* _48 = nullptr;
};
KSYS_CHECK_SIZE_NX150(Handle, 0x50);

}  // namespace ksys::res
