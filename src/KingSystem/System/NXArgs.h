#pragma once

#include <basis/seadNew.h>
#include <codec/seadHashCRC32.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class nxargs {
    SEAD_SINGLETON_DISPOSER(nxargs)
    nxargs() = default;
    virtual ~nxargs();

public:
    enum class LaunchParamFlag {
        hasDropActor = 1 << 0,  // 1
        _2 = 1 << 1,            // 2
    };
    struct LaunchParamEntry {
        u32 mActorNameHash;
        u32 mDropActorNameHash;
        sead::Vector3f mPositionOffset{};
        sead::Vector3f mRotate{};
        sead::Vector3f mVelocity{};
        LaunchParamFlag mFlags;
        char mNumConditions;
    };

    enum argstype {
        TypeNone = 0,
        TypeCreateActors = 1,
    };

    struct ResLaunchParamDataHeader {
        char magic[4] = {'B', 'o', 't', 'W'};
        u16 _4;
        u8 _6;
        argstype type;
        u32 padding;
        u8 numActorEntries;
        u8 padding2[3];
    };

    struct ResLaunchParamData {
        ResLaunchParamDataHeader header;
    };

    enum LaunchParamEntryConditionDataType {
        DataType_Bool = 1,
        DataType_S32 = 2,
        DataType_F32 = 3,
    };

    struct LaunchParamEntryCondition {
        sead::HashCRC32 flagNameHash;
        float rhsValue;
        LaunchParamEntryConditionDataType flagDataType;
        u8 operation;
    };
    
    struct LaunchParamEntrySpawnCondition {
        int resField0;
        int resField8;
        u8 resField4;
        u8 resField5;
    };

    void init(sead::Heap* heap);
    void allocEntries(sead::Heap *heap, nxargs::ResLaunchParamData *data);
    void handleArgs();

    u16 mResField4 = 0;
    u8 mResField6;
    u8 mType;
    u8 mNumEntries = 0;
    sead::Buffer<LaunchParamEntry> mEntries; //(int size, LaunchParamEntry* data);
    sead::Buffer<LaunchParamEntrySpawnCondition> mSpawnCondition; //(int size, LaunchParamEntryCondition* data);

    bool mHasHandledArgs = false;

private:
};

}  // namespace ksys