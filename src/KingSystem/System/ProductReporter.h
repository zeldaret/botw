#pragma once

#include <math/seadVector.h>
#include <prim/seadEnum.h>
#include "KingSystem/GameData/gdtFlagHandle.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace sead {
class Heap;
}

namespace ksys {

class PlayReport;

SEAD_ENUM(PlayReportKey, PlayReport_PlayTime , PlayReport_AllPlayTime , PlayReport_CtrlMode_Free , PlayReport_CtrlMode_Ext , PlayReport_CtrlMode_FullKey , PlayReport_CtrlMode_Handheld , PlayReport_CtrlMode_Console_Free , PlayReport_CtrlMode_Console_Ext , PlayReport_CtrlMode_Console_FullKey , PlayReport_PlayTime_Handheld , PlayReport_PlayTime_Console , PlayReport_AudioChannel_Mono , PlayReport_AudioChannel_Stereo , PlayReport_AudioChannel_5_1ch , PlayReport_AudioChannel_Other , PosTrackEndPointBlockNumber , PosTrackEndPointRecordIndex , PosTrackEndPointPosIndex)

struct WorkTimes {
    util::InitConstants _0;
    u32 rom;
    u32 scene;
};

// TODO
class PlayerTrackReporter {
public:
    PlayerTrackReporter();
    void init(sead::Heap* heap);
    void setPosTrackEnd();

    u8 _0[40];
    bool _28;
    bool _29;
    bool _30;
    u8 _3a[5];
};

enum class PanicReason {
    OverlayArenaFull = 0,
    HavokMainHeapFull = 1,
    ActorCreateHeapFull = 2,
    ResourceSHeapFull = 3,
    ResourceLHeapFull = 4,
    AudioHeapFull = 5,
    TextureHandleMgrSlow = 6,
};

class ProductReporter {
public:
    ProductReporter() = default;
    virtual ~ProductReporter();

    void init(sead::Heap* heap);
    void initGameDataIterators();
    void terminate();

    static bool getSomeBool();
    bool isEnabled() const;

    sead::BitFlag32 getPanicReasons() const { return mPanicReasons; }
    void addPanicReason(PanicReason reason) { mPanicReasons.setBit(int(reason)); }
    void clearPanicReason() { mPanicReasons.makeAllZero(); }

    s32 getRomWorkTime() const;
    s32 getSceneWorkTime() const;
    void resetSceneWorkTime();

    void updateTimers();
    bool saveReport(PlayReport* playReport) const;
    bool incrementSceneAndRomWorkTime();

    s32 getPlayTime() const;
    s32 getAllPlayTime() const;
    s32 getCtrlModeFree() const;
    s32 getCtrlModeExt() const;
    s32 getCtrlModeFullKey() const;
    s32 getCtrlModeHandheld() const;
    s32 getCtrlModeConsoleFree() const;
    s32 getCtrlModeConsoleExt() const;
    s32 getCtrlModeConsoleFullKey() const;
    s32 getCtrlModePlayTimeHandheld() const;
    s32 getPlayTimeConsole() const;

    class Container {
    public:
        void init(sead::Heap* heap, u64 capacity, u64 itemSize) {
            auto* dataPointer = new (heap, 8, std::nothrow) u8[capacity * itemSize];
            if (dataPointer != nullptr) {
                mBuffer = dataPointer;
                mBufferLength = 0;
                mBufferCapacity = capacity;
            }
        }

    private:
        void* mBuffer;
        u64 mBufferCapacity;
        u32 mBufferLength;
    };

    sead::Heap* getHeap() const { return mHeap; }

    PlayerTrackReporter* getPlayerTrackReporter() const { return mPlayerTrackReporter; }

    inline s32 getS32(s32 key) {
        s32 out = 0;
        gdt::Manager::instance()->getS32(mGameDataHandles[key], &out);
        return out;
    }

private:
    sead::BitFlag32 mPanicReasons;

    Container mContainer1;
    Container mContainer2;
    Container mContainer3;
    Container mContainer4;

    f32 mNinetyTickTimer;
    f32 mIncrementWorkTimesTimer;
    f32 mCameraIdleTimer;

    sead::Vector3f mPos;
    sead::Heap* mHeap;
    bool mIsInitalized;
    bool mEnabled;
    u32 mCtrlMode;  // TODO: very likely an enum member
    PlayerTrackReporter* mPlayerTrackReporter;
    gdt::FlagHandle mGameDataHandles[PlayReportKey::size()];
    gdt::Manager::ReinitSignal::Slot mSlot;
};

}  // namespace ksys
