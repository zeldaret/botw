#include "KingSystem/Resource/resHandle.h"
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include <time/seadTickTime.h>
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Utils/Debug.h"

namespace ksys::res {

namespace {
struct UnusedVariables {
    sead::TickTime tick_time;
    void* _8 = nullptr;
    f32 _10 = 0.5;
    f32 _14 = 1.0;
    f32 _18 = 0.5;
    f32 _1c = 1.0;
};
}  // namespace

UnusedVariables sVariables;
const sead::SafeString sStatusStrings_[0x11] = {
    "            ",    // 0x0
    "[Unknown]   ",    // 0x1
    "[No File]   ",    // 0x2
    "[Request OK]",    // 0x3
    "[Already]   ",    // 0x4
    "[FromCache] ",    // 0x5
    "[No Memory] ",    // 0x6
    "[No Execute]",    // 0x7
    "[Size Zero] ",    // 0x8
    "[Compose NG]",    // 0x9
    "[AllocSizeNG]",   // 0xa
    "[Edited]    ",    // 0xb
    "[HeapSizeNG]",    // 0xc
    "[FileDeviceNG]",  // 0xd
    "[Load OK]",       // 0xe
    "[Yet]",           // 0xf
    "[Canceled]",      // 0x10
};
const sead::Buffer<const sead::SafeString> sStatusStrings{0x11, sStatusStrings_};

ILoadRequest::~ILoadRequest() {
    ;
}

LoadRequest::LoadRequest() = default;

LoadRequest::LoadRequest(s32 load_data_alignment, u32 arg_c, bool arg_20)
    : _20(arg_20), mLoadDataAlignment(load_data_alignment) {
    _c = arg_c;
}

SimpleLoadRequest::SimpleLoadRequest() = default;

SimplePackedLoadRequest::SimplePackedLoadRequest() = default;

Handle::Handle() = default;

Handle::~Handle() {
    requestUnload();
}

void Handle::requestUnload() {
    if (!mFlags.isOn(Flag::_2))
        return;

    mFlags.reset(Flag::_7);
    mFlags.set(Flag::_4);

    if (mTaskHandle.hasTask()) {
        mTaskHandle.removeTaskFromQueue();
        if (!mUnit) {
            stubbedLogFunction();
            mStatus = Status::_14;
            return;
        }
    }

    if (!mUnit)
        return;

    if (ResourceMgrTask::instance())
        ResourceMgrTask::instance()->requestUnload(this);
}

sead::DirectResource* Handle::getResource() const {
    if (!isSuccess())
        return nullptr;
    return mUnit->mResource;
}

bool Handle::isSuccess() const {
    if (mFlags.isOff(Flag::_2))
        return false;

    if (isBusy())
        return false;

    if (!mUnit || !mUnit->isParseOk())
        return false;

    return true;
}

sead::DirectResource* Handle::getResourceUnchecked() const {
    return mUnit->mResource;
}

Handle::Status Handle::getStatus() const {
    return mStatus;
}

void Handle::setStatusForResourceMgr_(const Status& status) {
    mStatus = status;
}

inline bool Handle::checkPathChange_(const sead::SafeString& path) {
    if (!mFlags.isOn(Flag::_2))
        return true;

    stubbedLogFunction();
    sead::FormatFixedSafeString<512> message("↓↓↓\n前回ファイル：%s\n今回ファイル：%s\n↑↑↑\n",
                                             mUnit ? mUnit->mPath.cstr() : "***", path.cstr());
    util::PrintDebug(message);
    return false;
}

sead::DirectResource* Handle::load(const sead::SafeString& path, const ILoadRequest* request,
                                   Handle::Status* out_status) {
    if (checkPathChange_(path)) {
        mFlags.reset(Flag::_F);
        mFlags.set(Flag::_2);
        mStatus = Status::_0;
        if (request) {
            ResourceMgrTask::instance()->requestLoadForSync(this, path, *request);
        } else {
            LoadRequest temp_request;
            ResourceMgrTask::instance()->requestLoadForSync(this, path, temp_request);
        }
        if (out_status)
            *out_status = mStatus;
    } else {
        if (out_status)
            *out_status = Status::_8;
    }

    return getResource();
}

bool Handle::isFlag2Set() const {
    return mFlags.isOn(Flag::_2);
}

bool Handle::requestLoad(const sead::SafeString& path, const ILoadRequest* request,
                         Handle::Status* out_status) {
    if (checkPathChange_(path)) {
        mFlags.reset(Flag::_F);
        mFlags.set(Flag::_2);
        mStatus = Status::_0;

        Handle::Status ret;
        if (request) {
            ret = ResourceMgrTask::instance()->requestLoad(this, path, *request);
        } else {
            LoadRequest temp_request;
            ret = ResourceMgrTask::instance()->requestLoad(this, path, temp_request);
        }

        if (out_status)
            *out_status = ret;

        return ret == Status::_7;
    }

    if (out_status)
        *out_status = Status::_8;

    return false;
}

bool Handle::waitForReady() {
    if (mTaskHandle.isTaskAttached())
        mTaskHandle.wait();

    if (mUnit)
        mUnit->waitForTask1();

    return true;
}

bool Handle::waitForReady(const sead::TickSpan& span) {
    if (mTaskHandle.isTaskAttached() && !mTaskHandle.wait(span))
        return false;

    if (mUnit && !mUnit->waitForTask1(span))
        return false;

    return true;
}

bool Handle::parseResource(Context* context) {
    if (mFlags.isOn(Flag::_8))
        return true;

    if (mFlags.isOn(Flag::_4))
        return false;

    if (mTaskHandle.getStatus() == util::ManagedTaskHandle::Status::TaskRemoved ||
        (mUnit && mUnit->isTask1NotQueued())) {
        stubbedLogFunction();
        mStatus = Status::_14;
        updateResourceMgrFlag_();
        requestUnload();
        mFlags.set(Flag::_8);
        return true;
    }

    if (mStatus == Status::_1 || mStatus == Status::_2 || mStatus == Status::_3 ||
        mStatus == Status::_8 || mStatus == Status::_9 || mStatus == Status::_10 ||
        mStatus == Status::_11 || mStatus == Status::_12 || mStatus == Status::_13 ||
        mStatus == Status::_14) {
        updateResourceMgrFlag_();
        requestUnload();
        mFlags.set(Flag::_8);
        return true;
    }

    if (mStatus == Status::_0)
        return false;

    if (!mUnit) {
        stubbedLogFunction();
        return false;
    }

    switch (mUnit->getStatus()) {
    case ResourceUnit::Status::_0:
    case ResourceUnit::Status::_7:
        return false;
    case ResourceUnit::Status::_8:
    case ResourceUnit::Status::_10:
    case ResourceUnit::Status::_11:
    case ResourceUnit::Status::_13:
        waitForResourceAndParse_(context);
        break;
    case ResourceUnit::Status::_9:
        updateStatusAndUnload_();
        break;
    case ResourceUnit::Status::_12:
    case ResourceUnit::Status::_15:
        mStatus = Status::_9;
        updateResourceMgrFlag_();
        requestUnload();
        mFlags.set(Flag::_8);
        return true;
    case ResourceUnit::Status::_14:
        if (mStatus == Status::_7)
            mStatus = Status::_4;
        updateResourceMgrFlag_();
        break;
    default:
        break;
    }

    mFlags.set(Flag::_8);
    return true;
}

bool Handle::isFlag8Set() const {
    return mFlags.isOn(Flag::_8);
}

// NON_MATCHING: switch
void Handle::updateResourceMgrFlag_() {
    sead::FixedSafeString<128> path("***");
    if (mUnit)
        path = mUnit->mPath;

    bool warn = true;
    switch (mStatus) {
    case Status::_3:
        if (!mUnit || !mUnit->mArena1->isFlag1Set())
            break;
        if (!returnFalse())
            warn = false;
        break;
    case Status::_4:
        static_cast<void>(static_cast<volatile ResourceUnit*>(mUnit)->mStatusFlags);
        if (!returnFalse())
            warn = false;
        break;
    case Status::_5:
    case Status::_6:
    case Status::_8:
        if (!returnFalse())
            warn = false;
        break;
    default:
        break;
    }

    if (warn)
        stubbedLogFunction();

    if (mStatus != Status::_3 || !mUnit || !mUnit->mArena1)
        return;

    auto* heap = mUnit->mArena1->getHeap();

    if (!mUnit->mArena1->isFlag1Set() || returnFalse())
        stubbedLogFunction();

    if (!mUnit->mArena1->isFlag10Set())
        return;

    const s32 type =
        (heap->getName().startsWith("Sound") || heap->getName().startsWith("Audio")) ? 0 : 1;
    res::ResourceMgrTask::instance()->setFlag2000Or5000(type);
}

void Handle::updateStatusAndUnload_() {
    auto* unit = mUnit;
    if (unit && unit->isStatus9_12_15()) {
        mStatus = [&] {
            if (unit->mStatusFlags.isOn(ResourceUnit::StatusFlag::FailedMaybe))
                return Status::_1;
            if (unit->mStatusFlags.isOn(ResourceUnit::StatusFlag::FileSizeIsZero))
                return Status::_2;
            if (unit->mStatusFlags.isOn(ResourceUnit::StatusFlag::_400))
                return Status::_9;
            if (unit->mStatusFlags.isOn(ResourceUnit::StatusFlag::FileSizeExceedsAllocSize))
                return Status::_10;
            if (unit->mStatusFlags.isOn(ResourceUnit::StatusFlag::_1000))
                return Status::_11;
            if (unit->mStatusFlags.isOn(ResourceUnit::StatusFlag::FileOrResInstanceTooLargeForHeap))
                return Status::_12;
            if (unit->mStatusFlags.isOn(ResourceUnit::StatusFlag::LoadFailed))
                return Status::_13;

#ifdef MATCHING_HACK_NX_CLANG
            asm("");
#endif
            return Status::_3;
        }();
    }
    updateResourceMgrFlag_();
    requestUnload();
}

void Handle::requestUnload2() {
    requestUnload();
}

void Handle::unload() {
    if (!mFlags.isOn(Flag::_2))
        return;

    mFlags.reset(Flag::_7);
    mFlags.set(Flag::_4);

    if (mTaskHandle.hasTask()) {
        mTaskHandle.removeTaskFromQueue();
        if (!mUnit) {
            stubbedLogFunction();
            mStatus = Status::_14;
            return;
        }
    }

    if (mUnit)
        ResourceMgrTask::instance()->requestUnloadForSync(this);
}

void Handle::unloadAndResetUnitFlag20000() {
    if (!mFlags.isOn(Flag::_2))
        return;

    mFlags.reset(Flag::_7);
    mFlags.set(Flag::_4);

    if (mTaskHandle.hasTask()) {
        mTaskHandle.removeTaskFromQueue();
        if (!mUnit) {
            stubbedLogFunction();
            mStatus = Status::_14;
            return;
        }
    }

    ResourceUnit* unit = mUnit;
    if (!unit)
        return;

    stubbedLogFunction();
    unit->mStatusFlags.reset(ResourceUnit::StatusFlag::_20000);
    ResourceMgrTask::instance()->requestUnloadForSync(this);
}

void Handle::resetUnitFlag20000IfSuccess() {
    if (mFlags.isOff(Flag::_2))
        return;

    ResourceUnit* unit = mUnit;

    if (isBusy())
        return;

    if (!mUnit || !mUnit->isParseOk())
        return;

    if (unit)
        unit->mStatusFlags.reset(ResourceUnit::StatusFlag::_20000);
}

bool Handle::isBusy() const {
    if (mTaskHandle.isTaskAttached())
        return true;

    if (mFlags.isOn(Flag::_2) && mUnit)
        return mUnit->isTask1ActiveOrStatus7();

    return false;
}

bool Handle::isReadyOrNeedsParse() const {
    if ((mFlags.getDirect() & 0xA) != u32(Flag::_2) || isBusy())
        return false;

    if (isReady())
        return true;

    return mUnit && mUnit->needsParse();
}

bool Handle::isReady() const {
    if (isSuccess())
        return true;

    return checkLoadStatus();
}

bool Handle::checkLoadStatus() const {
    if (isBusy())
        return false;

    bool ok = false;
    if (mFlags.isOn(Flag::_2) && mUnit)
        ok = mUnit->isStatus9_12_15();

    ok |= mStatus == Status::_1 || mStatus == Status::_2 || mStatus == Status::_3 ||
          mStatus == Status::_8 || mStatus == Status::_9 || mStatus == Status::_10 ||
          mStatus == Status::_11 || mStatus == Status::_12 || mStatus == Status::_13 ||
          mStatus == Status::_14;

    return ok;
}

sead::SafeString Handle::makeEmptyString() {
    return sead::SafeString::cEmptyString;
}

void Handle::waitForResourceAndParse_(Context* context) {
    if (!mUnit) {
        updateResourceMgrFlag_();
        return;
    }

    if (mUnit->waitForResourceAndParse(context)) {
        if (mStatus == Status::_7)
            mStatus = Status::_4;
        updateResourceMgrFlag_();
        return;
    }

    mStatus = Status::_9;
    updateResourceMgrFlag_();
    requestUnload();
}

}  // namespace ksys::res
