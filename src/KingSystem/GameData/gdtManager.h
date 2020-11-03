#pragma once

#include <container/seadRingBuffer.h>
#include <container/seadSafeArray.h>
#include <filedevice/seadArchiveFileDevice.h>
#include <framework/seadMethodTree.h>
#include <heap/seadDisposer.h>
#include <prim/seadDelegateEventSlot.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/System/KingEditor.h"
#include "KingSystem/Utils/Byaml.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Framework;
class MethodTreeMgr;
}  // namespace sead

namespace ksys::gdt {

class TriggerParam;

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

    struct TriggerParamRef {
        TriggerParamRef(TriggerParam** param_1, TriggerParam** param, bool check_permissions,
                        bool propagate_param_1_changes, bool change_only_once)
            : param1(param_1), param(param), check_permissions(check_permissions),
              propagate_param1_changes(propagate_param_1_changes),
              change_only_once(change_only_once) {}

        virtual ~TriggerParamRef() = default;

        TriggerParam** param1;
        TriggerParam** param;
        bool check_permissions;
        bool propagate_param1_changes;
        bool change_only_once;
    };
    KSYS_CHECK_SIZE_NX150(TriggerParamRef, 0x20);

    sead::Heap* getGameDataHeap() const { return mGameDataHeap; }
    sead::Heap* getSaveAreaHeap() const { return mSaveAreaHeap; }
    sead::Heap* getGameDataComHeap() const { return mGameDataComHeap; }

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
    u32 mParam1Flag = 0;

    sead::DelegateEvent<ReinitEvent*> mReinitEvent;
    sead::DelegateEvent<ResetEvent*> mResetEvent;

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
