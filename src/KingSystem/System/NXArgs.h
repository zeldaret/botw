#pragma once

#include <basis/seadNew.h>
#include <codec/seadHashCRC32.h>
#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <heap/seadExpHeap.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <nn/oe.h>
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
        u8 mNumConditions;
    };

    enum class argstype {
        TypeNone = 0,
        TypeCreateActors = 1,
    };

    struct ResLaunchParamDataHeader {
        char magic[4] = {'B', 'o', 't', 'W'};
        u16 _4;
        u8 _6;
        argstype type;
        u32 padding;
        u8 numactorentries;
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
        sead::HashCRC32 flagnamehash;
        float rhsvalue;
        LaunchParamEntryConditionDataType flagdatatype;
        u8 operation;
    };

    struct LaunchParamEntrySpawnCondition {
        int resfield0;
        int resfield8;
        u8 resfield4;
        u8 resfield5;
    };

    void init(sead::Heap* heap);
    void allocEntries(sead::Heap* heap, nxargs::ResLaunchParamData* data);
    void handleArgs();

    u8 mResField6;
    u8 mType;
    u8 mNumEntries = 0;
    sead::Buffer<LaunchParamEntry> mEntries;
    s16 mResField4 = 0;

    bool mHasHandledArgs = false;

private:
};
// KSYS_CHECK_SIZE_NX150(nxargs, 0x48);

}  // namespace ksys