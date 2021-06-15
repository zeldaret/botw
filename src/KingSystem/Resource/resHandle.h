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

class Context;
class ILoadRequest;
class ResourceUnit;

class Handle {
    SEAD_RTTI_BASE(Handle)
public:
    enum class Status {
        /// "No File" (2)
        NoFile = 0,
        _1 = 1,
        /// "Size Zero" (8)
        SizeZero = 2,
        _3 = 3,
        _4 = 4,
        _5 = 5,
        _6 = 6,
        _7 = 7,
        _8 = 8,
        /// "Compose NG" (9)
        ParseFailed = 9,
        /// "AllocSizeNG" (10)
        BadAllocSize = 10,
        /// "Edited" (11)?
        Edited = 11,
        /// "HeapSizeNG" (12)
        BadHeapSize = 12,
        /// "FileDeviceNG" (13)
        FileDeviceError = 13,
        /// "Canceled" (16)
        Cancelled = 14,
        /// Unknown
        Unknown = 15,
    };

    Handle();
    virtual ~Handle();

    Status getStatus() const;

    sead::DirectResource* getResource() const;
    bool isSuccess() const;
    sead::DirectResource* getResourceUnchecked() const;

    sead::DirectResource* load(const sead::SafeString& path, const ILoadRequest* request,
                               Status* out_status = nullptr);
    bool requestedLoad() const;
    bool requestLoad(const sead::SafeString& path, const ILoadRequest* request,
                     Status* out_status = nullptr);

    bool waitForReady();
    bool waitForReady(const sead::TickSpan& span);

    bool parseResource(Context* context);
    bool hasParsedResource() const;

    void requestUnload();
    void unload();
    // TODO: how does this differ?
    void requestUnload2();
    void unloadAndResetUnitFlag20000();
    void resetUnitFlag20000IfSuccess();

    bool isBusy() const;
    bool isReadyOrNeedsParse() const;
    bool isReady() const;
    bool checkLoadStatus() const;

    sead::SafeString makeEmptyString();

    ResourceUnit* getUnit() const { return mUnit; }
    void setUnit(ResourceUnit* unit) { mUnit = unit; }

    bool isLinked() const { return mListNode.isLinked(); }

    void setStatusForResourceMgr_(const Status& status);

    static size_t getListNodeOffset() { return offsetof(Handle, mListNode); }

private:
    enum class Flag : u8 {
        Dummy = 0x1,
        LoadRequested = 0x2,
        UnloadRequested = 0x4,
        LoadUnloadFlags = Dummy | LoadRequested | UnloadRequested,
        Parsed = 0x8,
        AllStatusFlags = LoadUnloadFlags | Parsed,
    };

    void updateResourceMgrFlag_();
    void updateStatusAndUnload_();
    void waitForResourceAndParse_(Context* context);

    inline bool checkPathChange_(const sead::SafeString& path);

    sead::TypedBitFlag<Flag> mFlags = Flag::Dummy;
    Status mStatus = Status::NoFile;
    ResourceUnit* mUnit = nullptr;
    util::ManagedTaskHandle mTaskHandle;
    sead::ListNode mListNode;
};
KSYS_CHECK_SIZE_NX150(Handle, 0x50);

}  // namespace ksys::res
