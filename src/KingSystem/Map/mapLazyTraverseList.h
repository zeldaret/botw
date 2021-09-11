#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {

class LazyTraverseList {
public:
    LazyTraverseList(sead::Heap* heap);
    ~LazyTraverseList();
    void updateFlags();

private:
    struct Entry {
        sead::FixedSafeString<0x40> flagName;
        bool flagValue;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x60);

    struct Object {
        u32 hashId;
        u32 entryIdx;
    };
    KSYS_CHECK_SIZE_NX150(Object, 0x8);

    sead::Buffer<Entry> entries;
    sead::Buffer<Object> objects;
    bool hasEntries = false;
};
KSYS_CHECK_SIZE_NX150(LazyTraverseList, 0x28);

}  // namespace ksys::map