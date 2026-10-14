#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys {
class OcclusionQueryCylinder;
}

namespace ksys::act {

class Actor;

class LodState {
public:
    LodState(sead::Heap* heap, sead::BitFlag32 flags, Actor* actor, int disable_calc_skip_frame,
             float x);
    virtual ~LodState();

private:
    void initFlags();

    sead::BitFlag64 mFlags8;
    sead::BitFlag32 mFlags10;
    sead::BitFlag32 mFlags14;
    sead::BitFlag32 mFlags18;
    u32 _1c = 4;
    u32 mActorType = 9;
    u8 _24 = 0xff;
    u8 _25;
    sead::BitFlag16 mFlags26;
    float _28 = 1.0;
    Actor* mActor = nullptr;
    OcclusionQueryCylinder* mOcclusionQueryCylinder = nullptr;
    float _40 = 0.0;
    float _44 = 0.0;
    float _48 = 0.0;
    float mDistanceScale = 1.0;
    float _50 = 1.0;
    float mDispDistance = 0.0;
    float _58 = -1.0;
    int mDisableCalcSkipFrame = 0;
    u32 _60 = 0;
    int _64 = -3;
    float _68;
    float _6c;
    u32 _70;
    float _74;
    float _78 = 0.0;
};
KSYS_CHECK_SIZE_NX150(LodState, 0x80);

}  // namespace ksys::act
