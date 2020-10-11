#pragma once

#include <container/seadListImpl.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class DirectResource;
}

namespace ksys::res {

class ILoadRequest;
class ResourceUnit;

// FIXME: incomplete
class Handle {
    SEAD_RTTI_BASE(Handle)
public:
    enum class Status {
        _0 = 0,
        _1 = 1,
        _2 = 2,
        _3 = 3,
        _4 = 4,
        _5 = 5,
        _6 = 6,
        _7 = 7,
        _8 = 8,
        _9 = 9,
        _10 = 10,
        _11 = 11,
        _12 = 12,
        _13 = 13,
        _14 = 14,
    };

    Handle();
    virtual ~Handle();

    Status getStatus() const;

    sead::DirectResource* load(const sead::SafeString& path, const ILoadRequest& request,
                               Status* out_status = nullptr);

    void unload();

    void setUnit(ResourceUnit* unit) { mUnit = unit; }

    bool isLinked() const { return mListNode.isLinked(); }

    static size_t getListNodeOffset() { return offsetof(Handle, mListNode); }

private:
    enum class Flag : u8 {
        _1 = 0x1,
        _2 = 0x2,
        _4 = 0x4,
        _7 = 0x7,
        _8 = 0x8,
    };

    sead::TypedBitFlag<Flag> mFlags = Flag::_1;
    Status mStatus = Status::_0;
    ResourceUnit* mUnit = nullptr;
    util::ManagedTaskHandle mTaskHandle;
    sead::ListNode mListNode;
};
KSYS_CHECK_SIZE_NX150(Handle, 0x50);

}  // namespace ksys::res
