#pragma once

#include <basis/seadNew.h>
#include <codec/seadHashCRC32.h>
#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <heap/seadExpHeap.h>
#include <math/seadVector.h>
#include <nn/oe.h>
#include <prim/seadSafeString.h>
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace ksys {

class nxargs {
    SEAD_SINGLETON_DISPOSER(nxargs)
    nxargs() {
        mNumEntries = 0;
        mResField4 = 0;
        mResField6 = 0;
        mType = ArgsType::None;
    }
    virtual ~nxargs();

public:
    enum class LaunchParamFlag : u8 {
        hasDropActor = 1 << 0,  // 1
        _2 = 1 << 1,            // 2
    };
    struct LaunchParamEntrySpawnCondition {
        int resfield0;
        int resfield8;
        u8 resfield4;
        u8 resfield5;
    };
    struct LaunchParamEntry {
        u32 mActorNameHash;
        u32 mDropActorNameHash;
        sead::Vector3f mPositionOffset{};
        sead::Vector3f mRotate{};
        sead::Vector3f mVelocity{};
        LaunchParamFlag mFlags;
        u8 mNumConditions;
        sead::Buffer<LaunchParamEntrySpawnCondition> mConditions;
    };

    enum class ArgsType : u8 {
        None = 0,
        CreateActors = 1,
    };

    struct ResLaunchParamDataHeader {
        char magic[4];
        u16 _4;
        u8 _6;
        ArgsType type;
        u32 padding;
        u8 numentries;
        u8 padding2[3];
    };

    struct ResLaunchParamData {
        ResLaunchParamDataHeader header;
        u8 padding[0xFF0];
    };

    enum LaunchParamEntryConditionDataType : u8 {
        DataType_Bool = 1,
        DataType_S32 = 2,
        DataType_F32 = 3,
    };

    struct LaunchParamEntryCondition {
        sead::HashCRC32 flagnamehash;
        float rhsvalue;
        LaunchParamEntryConditionDataType flagdatatype;
        u8 operation;
    };

    void init(sead::Heap* heap);
    void allocEntries(sead::Heap* heap, nxargs::ResLaunchParamData* data);
    void handleArgs();

private:
    u16 mResField4 = 0;
    u8 mResField6;
    ArgsType mType;
    u8 mNumEntries = 0;
    sead::Buffer<LaunchParamEntry> mEntries;
    bool mHasHandledArgs = false; 
};
KSYS_CHECK_SIZE_NX150(nxargs, 0x48);

}  // namespace ksys