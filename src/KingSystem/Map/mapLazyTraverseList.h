#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {

class LazyTraverseList {
public:
    explicit LazyTraverseList(sead::Heap* heap);
    ~LazyTraverseList();
    void updateFlags();
    bool wereFlagsUpdated();

    bool empty() const { return !mHasEntries; }

private:
    struct Entry {
        sead::FixedSafeString<0x40> flag_name;
        bool flag_value;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x60);

    struct Object {
        u32 hash_id;
        u32 entry_idx;
    };
    KSYS_CHECK_SIZE_NX150(Object, 0x8);

    sead::Buffer<Entry> mEntries;
    sead::Buffer<Object> mObjects;
    bool mHasEntries = false;
};
KSYS_CHECK_SIZE_NX150(LazyTraverseList, 0x28);

}  // namespace ksys::map
