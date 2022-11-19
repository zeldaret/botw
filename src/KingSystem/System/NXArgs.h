#pragma once

#include <basis/seadNew.h>
#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <heap/seadExpHeap.h>
#include <math/seadVector.h>
#include <nn/oe.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class nxargs {
    SEAD_SINGLETON_DISPOSER(nxargs)
    nxargs() : mResField4{0}, mResField6{0}, mType{ArgsType::None}, mNumEntries{0} {}
    virtual ~nxargs();

public:
    enum class LaunchParamFlag : u8 {
        None = 0,
        HasDropActor = 1,
        _2 = 2,
    };

    struct LaunchParamEntrySpawnCondition {
        u32 resfield0;
        u32 resfield8;
        u8 resfield4;
        u8 resfield5;
    };

    enum class LaunchParamEntryConditionDataType : u8 {
        None = 0,
        Bool = 1,
        S32 = 2,
        F32 = 3,
    };

    enum class ActorEntryConditionOperation : u8 {
        None = 0,
        Eq = 1,
        NotEq = 2,
        Gt = 3,
        Gte = 4,
        Lt = 5,
        Lte = 6,
    };

    struct LaunchParamEntryCondition {
        s32 flagNameHash;
        f32 rhsValue;
        LaunchParamEntryConditionDataType flagDataType;
        ActorEntryConditionOperation operation;
    };

    struct LaunchParamEntry {
        u32 actorNameHash;
        u32 dropActorNameHash;
        sead::Vector3f positionOffset;
        sead::Vector3f rotation;
        sead::Vector3f velocity;
        LaunchParamFlag flags{};
        u8 numConditions;
        sead::Buffer<LaunchParamEntryCondition> conditions;
    };

    KSYS_CHECK_SIZE_NX150(LaunchParamEntry, 0x40);

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
        u8 numEntries;
        u8 padding2[3];
    };

    void init(sead::Heap* heap);
    void allocEntries(sead::Heap* heap, const u8* data);
    void handleArgs();

private:
    u16 mResField4;
    u8 mResField6;
    ArgsType mType;
    u8 mNumEntries;
    sead::Buffer<LaunchParamEntry> mEntries;
    bool mHasHandledArgs = false;
};
KSYS_CHECK_SIZE_NX150(nxargs, 0x48);

}  // namespace ksys