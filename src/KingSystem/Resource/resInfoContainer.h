#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class ResourceInfoContainer {
public:
    ResourceInfoContainer();
    virtual ~ResourceInfoContainer();

    bool loadResourceSizeTable();
    u32 getResourceSize(const sead::SafeString& name);

private:
    struct ResEntry {
        static s32 compareT(const ResEntry* lhs, const ResEntry* rhs) {
            if (*lhs > *rhs)
                return 1;
            if (*lhs < *rhs)
                return -1;
            return 0;
        }

        bool operator<(const ResEntry& other) const { return res_name_hash < other.res_name_hash; }
        bool operator>(const ResEntry& other) const { return res_name_hash > other.res_name_hash; }
        u32 res_name_hash;
        s32 res_size;
    };

    struct ResStringEntry {
        s32 compare(const sead::SafeString& name) const;

        char res_name[128];
        s32 res_size;
    };

    Handle mRstbHandle;
    sead::Buffer<const ResEntry> mEntries;
    sead::Buffer<const ResStringEntry> mStringEntries;
};
KSYS_CHECK_SIZE_NX150(ResourceInfoContainer, 0x78);

}  // namespace ksys::res
