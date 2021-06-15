#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include <resource/seadResource.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class FileDevice;
}

namespace ksys {
class OverlayArena;
}

namespace ksys::res {

class Handle;

class EntryFactoryBase;

class ILoadRequest {
    SEAD_RTTI_BASE(ILoadRequest)
public:
    ILoadRequest() = default;
    ILoadRequest(const ILoadRequest&) = default;
    ILoadRequest& operator=(const ILoadRequest&) = default;
    virtual ~ILoadRequest();

    bool _8 = false;
    u32 _c = 1;
    sead::SafeString mRequester;
};
KSYS_CHECK_SIZE_NX150(ILoadRequest, 0x20);

class LoadRequest : public ILoadRequest {
    SEAD_RTTI_OVERRIDE(LoadRequest, ILoadRequest)
public:
    LoadRequest();
    LoadRequest(s32 load_data_alignment, u32 arg_c, bool arg_20);
    LoadRequest(const LoadRequest&) = default;
    LoadRequest& operator=(const LoadRequest&) = default;
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
    u32 mBufferSize = 0;
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

class SimpleLoadRequest : public ILoadRequest {
    SEAD_RTTI_OVERRIDE(SimpleLoadRequest, ILoadRequest)
public:
    SimpleLoadRequest();
    ~SimpleLoadRequest() override = default;
    SimpleLoadRequest(const SimpleLoadRequest&) = default;
    SimpleLoadRequest& operator=(const SimpleLoadRequest&) = default;

    sead::SafeString mPath;
    void* _30 = nullptr;
};
KSYS_CHECK_SIZE_NX150(SimpleLoadRequest, 0x38);

class SimplePackedLoadRequest : public ILoadRequest {
    SEAD_RTTI_OVERRIDE(SimplePackedLoadRequest, ILoadRequest)
public:
    SimplePackedLoadRequest();
    ~SimplePackedLoadRequest() override = default;
    SimplePackedLoadRequest(const SimplePackedLoadRequest&) = default;
    SimplePackedLoadRequest& operator=(const SimplePackedLoadRequest&) = default;

    Handle* mPack = nullptr;
    void* _30 = nullptr;
};
KSYS_CHECK_SIZE_NX150(SimplePackedLoadRequest, 0x30);

}  // namespace ksys::res
