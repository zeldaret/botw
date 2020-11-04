#pragma once

#include <container/seadRingBuffer.h>
#include <container/seadSafeArray.h>
#include <filedevice/seadArchiveFileDevice.h>
#include <framework/seadMethodTree.h>
#include <heap/seadDisposer.h>
#include <prim/seadDelegateEventSlot.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/GameData/gdtTriggerParam.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/System/KingEditor.h"
#include "KingSystem/Utils/Byaml.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Framework;
class MethodTreeMgr;
}  // namespace sead

namespace ksys::gdt {

enum class FlagHandle : u32 {};

class TriggerParamRef {
public:
    TriggerParamRef(TriggerParam** param_1, TriggerParam** param, bool check_permissions,
                    bool propagate_param_1_changes, bool change_only_once)
        : mParam1(param_1), mParam(param), mCheckPermissions(check_permissions),
          mPropagateParam1Changes(propagate_param_1_changes), mChangeOnlyOne(change_only_once) {}

    virtual ~TriggerParamRef() = default;

    class Proxy {
    public:
        TriggerParam* getBuffer() const { return mUseParam1 ? *mRef.mParam1 : *mRef.mParam; }

        // region Value getters

#define PROXY_GET_SET_IMPL_(GET_NAME, SET_NAME, TYPE)                                              \
    bool GET_NAME(TYPE* value, s32 index) const {                                                  \
        return getBuffer()->GET_NAME(value, index, mRef.mCheckPermissions);                        \
    }                                                                                              \
    bool GET_NAME(TYPE* value, s32 array_index, s32 index) const {                                 \
        return getBuffer()->GET_NAME(value, array_index, index, mRef.mCheckPermissions);           \
    }                                                                                              \
    bool GET_NAME(TYPE* value, const sead::SafeString& name) const {                               \
        return getBuffer()->GET_NAME(value, name, mRef.mCheckPermissions);                         \
    }                                                                                              \
    bool GET_NAME(TYPE* value, const sead::SafeString& array_name, s32 index) const {              \
        return getBuffer()->GET_NAME(value, array_name, index, mRef.mCheckPermissions);            \
    }                                                                                              \
                                                                                                   \
    bool SET_NAME(TYPE const& value, s32 idx, bool bypass_one_trigger_check = false) {             \
        if (mRef.mChangeOnlyOne)                                                                   \
            return false;                                                                          \
        return getBuffer()->SET_NAME(value, idx, mRef.mCheckPermissions,                           \
                                     bypass_one_trigger_check);                                    \
    }                                                                                              \
    bool SET_NAME(TYPE const& value, s32 array_idx, s32 idx,                                       \
                  bool bypass_one_trigger_check = false) {                                         \
        if (mRef.mChangeOnlyOne)                                                                   \
            return false;                                                                          \
        return getBuffer()->SET_NAME(value, array_idx, idx, mRef.mCheckPermissions,                \
                                     bypass_one_trigger_check);                                    \
    }                                                                                              \
    bool SET_NAME(TYPE const& value, const sead::SafeString& name,                                 \
                  bool bypass_one_trigger_check = false) {                                         \
        if (mRef.mChangeOnlyOne)                                                                   \
            return false;                                                                          \
        return getBuffer()->SET_NAME(value, name, mRef.mCheckPermissions, true,                    \
                                     bypass_one_trigger_check);                                    \
    }                                                                                              \
    bool SET_NAME(TYPE const& value, const sead::SafeString& name, s32 idx,                        \
                  bool bypass_one_trigger_check = false) {                                         \
        if (mRef.mChangeOnlyOne)                                                                   \
            return false;                                                                          \
        return getBuffer()->SET_NAME(value, name, idx, mRef.mCheckPermissions, true,               \
                                     bypass_one_trigger_check);                                    \
    }

        PROXY_GET_SET_IMPL_(getBool, setBool, bool)
        PROXY_GET_SET_IMPL_(getS32, setS32, s32)
        PROXY_GET_SET_IMPL_(getF32, setF32, f32)
        PROXY_GET_SET_IMPL_(getStr, setStr, char const*)
        PROXY_GET_SET_IMPL_(getStr64, setStr64, char const*)
        PROXY_GET_SET_IMPL_(getStr256, setStr256, char const*)
        PROXY_GET_SET_IMPL_(getVec2f, setVec2f, sead::Vector2f)
        PROXY_GET_SET_IMPL_(getVec3f, setVec3f, sead::Vector3f)
        PROXY_GET_SET_IMPL_(getVec4f, setVec4f, sead::Vector4f)

#undef PROXY_GET_SET_IMPL_

    private:
        friend class TriggerParamRef;
        Proxy(const TriggerParamRef& ref, bool param1) : mUseParam1(param1), mRef(ref) {}

        bool mUseParam1;
        const TriggerParamRef& mRef;
    };

    Proxy getParam() const { return Proxy(*this, false); }
    Proxy getParam1() const { return Proxy(*this, true); }

    void setBuffers(TriggerParam** param1, TriggerParam** param) {
        mParam1 = param1;
        mParam = param;
    }

    bool shouldCheckPermissions() const { return mCheckPermissions; }
    bool shouldPropagateParam1Changes() const { return mPropagateParam1Changes; }
    bool shouldChangeOnlyOne() const { return mChangeOnlyOne; }

    void setCheckPermissions(bool on) { mCheckPermissions = on; }
    void setPropagateParam1Changes(bool on) { mPropagateParam1Changes = on; }
    void setChangeOnlyOne(bool on) { mChangeOnlyOne = on; }

private:
    TriggerParam** mParam1;
    TriggerParam** mParam;
    bool mCheckPermissions;
    bool mPropagateParam1Changes;
    bool mChangeOnlyOne;
};
KSYS_CHECK_SIZE_NX150(TriggerParamRef, 0x20);

class IManager {
public:
    virtual ~IManager() = 0;
};

inline IManager::~IManager() = default;

/// GameDataMgr communication.
class ManagerCom : public KingEditorComponent {
public:
    void* _8 = nullptr;
    void* _10 = nullptr;
};
KSYS_CHECK_SIZE_NX150(ManagerCom, 0x18);

class Manager : public IManager, public ManagerCom {
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();
    ~Manager() override;
    const char* getName() const override { return "GameData"; }
    void syncData() override;

public:
    struct ResetEvent {
        virtual ~ResetEvent() = default;
        TriggerParam* param = nullptr;
    };

    struct ReinitEvent {
        virtual ~ReinitEvent() = default;
    };

    using ResetSignal = sead::DelegateEvent<ResetEvent*>;
    using ReinitSignal = sead::DelegateEvent<ReinitEvent*>;

    sead::Heap* getGameDataHeap() const { return mGameDataHeap; }
    sead::Heap* getSaveAreaHeap() const { return mSaveAreaHeap; }
    sead::Heap* getGameDataComHeap() const { return mGameDataComHeap; }

    TriggerParamRef& getParam() { return mParam; }
    TriggerParamRef& getParamBypassPerm() { return mParamBypassPerm; }

#define GDT_GET_HANDLE_(NAME, GET_IDX_NAME)                                                        \
    FlagHandle NAME(const sead::SafeString& name) const {                                          \
        const auto prefix = mCurrentFlagHandlePrefix;                                              \
        const auto hash = sead::HashCRC32::calcStringHash(name);                                   \
        return makeFlagHandle(prefix, mParam.getParam1().getBuffer()->GET_IDX_NAME(hash));         \
    }

    GDT_GET_HANDLE_(getBoolHandle, TriggerParam::getBoolIdx)
    GDT_GET_HANDLE_(getS32Handle, TriggerParam::getS32Idx)
    GDT_GET_HANDLE_(getF32Handle, TriggerParam::getF32Idx)
    GDT_GET_HANDLE_(getStrHandle, TriggerParam::getStrIdx)
    GDT_GET_HANDLE_(getStr64Handle, TriggerParam::getStr64Idx)
    GDT_GET_HANDLE_(getStr256Handle, TriggerParam::getStr256Idx)
    GDT_GET_HANDLE_(getVec2fHandle, TriggerParam::getVec2fIdx)
    GDT_GET_HANDLE_(getVec3fHandle, TriggerParam::getVec3fIdx)
    GDT_GET_HANDLE_(getVec4fHandle, TriggerParam::getVec4fIdx)

    GDT_GET_HANDLE_(getBoolArrayHandle, TriggerParam::getBoolArrayIdx)
    GDT_GET_HANDLE_(getS32ArrayHandle, TriggerParam::getS32ArrayIdx)
    GDT_GET_HANDLE_(getF32ArrayHandle, TriggerParam::getF32ArrayIdx)
    GDT_GET_HANDLE_(getStrArrayHandle, TriggerParam::getStrArrayIdx)
    GDT_GET_HANDLE_(getStr64ArrayHandle, TriggerParam::getStr64ArrayIdx)
    GDT_GET_HANDLE_(getStr256ArrayHandle, TriggerParam::getStr256ArrayIdx)
    GDT_GET_HANDLE_(getVec2fArrayHandle, TriggerParam::getVec2fArrayIdx)
    GDT_GET_HANDLE_(getVec3fArrayHandle, TriggerParam::getVec3fArrayIdx)
    GDT_GET_HANDLE_(getVec4fArrayHandle, TriggerParam::getVec4fArrayIdx)

#undef GDT_GET_HANDLE_

    void init(sead::Heap* heap, sead::Framework* framework);

private:
    enum class BitFlag {
        _1 = 0x1,
        _2 = 0x2,
        _4 = 0x4,
        _8 = 0x8,
        _10 = 0x10,
        _20 = 0x20,
        _40 = 0x40,
        _80 = 0x80,
        _100 = 0x100,
        _200 = 0x200,
        _400 = 0x400,
        _800 = 0x800,
        _1000 = 0x1000,
    };

    enum class ResetFlag {

    };

    struct MethodTreeNode {
        virtual ~MethodTreeNode() = default;
        sead::MethodTreeNode node{nullptr};
        sead::MethodTreeMgr* method_tree_mgr = nullptr;
    };

    struct IncrementLogger {
        struct Record {
            u8 _0 = 0;
            u32 _4 = 0;
            s32 _8 = -1;
            u32 _c = 0;
        };
        KSYS_CHECK_SIZE_NX150(Record, 0x10);

        u64 _0 = 0;
        sead::FixedRingBuffer<Record, 64> ring_buffers[6]{};
        sead::SafeArray<Record, 0xc0> arrays[2]{};
    };

    static FlagHandle makeFlagHandle(u32 prefix, s32 idx) {
        return FlagHandle(idx | (prefix << 24));
    }

    void loadGameData(const sead::SafeString& path);
    void loadShopGameDataInfo(const sead::SafeString& path);
    void unloadResources();

    sead::Heap* mGameDataHeap = nullptr;
    sead::Heap* mSaveAreaHeap = nullptr;
    sead::Heap* mGameDataComHeap = nullptr;
    res::Handle mGameDataArcHandle;
    sead::SafeArray<res::Handle, 32> mBgdataHandles;
    sead::ArchiveFileDevice mGameDataArc{nullptr};

    res::Handle mShopGameDataInfoHandle;
    al::ByamlIter mShopAreaInfoValues;
    const u8* mShopAreaInfoHashes = nullptr;
    al::ByamlIter mShopSoldOutInfoValues;
    const u8* mShopSoldOutInfoHashes = nullptr;

    TriggerParamRef mParamBypassPerm{&mFlagBuffer1, &mFlagBuffer, false, false, false};
    TriggerParamRef mParam{&mFlagBuffer1, &mFlagBuffer, true, false, false};

    IncrementLogger* mIncrementLogger = nullptr;

    TriggerParam* mFlagBuffer1;
    TriggerParam* mFlagBuffer;
    TriggerParam* mRetryBuffer;
    TriggerParam* mGimmickResetBuffer;

    sead::TypedBitFlag<BitFlag> mBitFlags;
    sead::TypedBitFlag<ResetFlag> mResetFlags;
    u32 _c20 = 0;
    u32 mNumFlagsToReset = 0;
    u32 mCurrentFlagHandlePrefix = 0;

    ReinitSignal mReinitSignal;
    ResetSignal mResetSignal;

    MethodTreeNode mMethodTreeNode;

    void* mDelegate1 = nullptr;  // FIXME: figure out what this is
    sead::IDelegateR<const sead::SafeString&>* mGetMapNameDelegate = nullptr;

    sead::FixedSafeString<64> mStr;  // TODO: rename
    u32 mTrackerBlockSaveNumberFlagCrc32 = 0;
    u32 mSyncStep = 0;
    sead::CriticalSection mCriticalSection;
};
KSYS_CHECK_SIZE_NX150(Manager, 0xdc8);

}  // namespace ksys::gdt
