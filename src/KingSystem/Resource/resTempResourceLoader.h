#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class DirectResource;
}

namespace ksys::res {

class ArchiveWork;

class TempResourceLoader {
public:
    struct InitArg {
        ArchiveWork* work;
    };

    struct LoadArg {
        bool retry_on_failure = true;
        bool use_handle = true;
        u32 ms_between_attempts = 0;
        LoadRequest load_req;
    };

    TempResourceLoader();
    ~TempResourceLoader();

    void unload();
    bool init(const InitArg& arg);
    bool isLoading() const;
    bool isSuccess() const;
    bool checkLoadStatus() const;
    void requestLoad(LoadArg& arg);
    sead::DirectResource* getResourceForLoadRequest(Context* context);
    sead::DirectResource* load(LoadArg& arg);
    sead::DirectResource* getResource() const;
    Handle::Status getHandleStatus() const;
    sead::FileDevice* getHandleFileDevice() const;
    u32 getWorkHeapSize() const;

private:
    enum class Flag : u8 {
        Loading = 1,
        IsRetryingLoad = 2,
    };

    void setRetryFlag() {
        if (mFlags.isOff(Flag::IsRetryingLoad)) {
            stubbedLogFunction();
            mFlags.set(Flag::IsRetryingLoad);
        } else if (returnFalse()) {
            stubbedLogFunction();
        }
    }

    void resetRetryFlag() {
        if (mFlags.isOn(Flag::IsRetryingLoad)) {
            stubbedLogFunction();
            mFlags.reset(Flag::IsRetryingLoad);
        } else if (returnFalse()) {
            stubbedLogFunction();
        }
    }

    void updateFlagsBeforeLoadingStarts() {
        mFlags.reset(Flag::Loading);
        mFlags.reset(Flag::IsRetryingLoad);
        mFlags.set(Flag::Loading);
    }

    sead::TypedBitFlag<Flag> mFlags;
    sead::DirectResource* mResource{};
    ArchiveWork* mWork{};
    Handle mHandle;
    LoadArg mLoadArg;
    sead::FixedSafeString<128> mPath;
};
KSYS_CHECK_SIZE_NX150(TempResourceLoader, 0x188);

}  // namespace ksys::res
