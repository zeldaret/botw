#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class FileDevice;
}

namespace ksys {
class OverlayArena;
}

namespace ksys::res {

class EntryFactoryBase;
class Handle;

class ILoadRequest {
    SEAD_RTTI_BASE(ILoadRequest)
public:
    virtual ~ILoadRequest();

    bool _8 = false;
    u32 _c = 1;
    sead::SafeString mRequester;
};
KSYS_CHECK_SIZE_NX150(ILoadRequest, 0x20);

// FIXME: incomplete
class LoadRequest : public ILoadRequest {
    SEAD_RTTI_OVERRIDE(LoadRequest, ILoadRequest)
public:
    LoadRequest();
    LoadRequest(s32 load_data_alignment, u32 arg_c, bool arg_20);
    ~LoadRequest() override = default;

    bool _20 = false;
    bool _21 = false;
    bool _22 = false;
    bool mCanFallBackToNonArchiveLoad = true;
    bool _24 = false;
    bool mLoadCompressed = true;
    bool _26 = true;
    bool _27 = true;
    bool _28 = true;
    s32 mLoadDataAlignment = 0;
    u32 mAllocSize = 0;
    u32 _34 = 0;
    sead::FileDevice* mFileDevice = nullptr;
    EntryFactoryBase* mEntryFactory = nullptr;
    sead::FileDevice* mAocFileDevice = nullptr;
    OverlayArena* mArena = nullptr;
    Handle* mPackHandle = nullptr;
    void* _60 = nullptr;
    void* _68 = nullptr;
    sead::SafeString mPath;
};
KSYS_CHECK_SIZE_NX150(LoadRequest, 0x80);

}  // namespace ksys::res
