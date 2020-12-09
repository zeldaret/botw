#pragma once

#include <prim/seadTypedBitFlag.h>
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/Map/mapMubinIter.h"

namespace ksys {

namespace act {

namespace ai {
class RootAi;
}

class LifeRecoverInfo;
class ActorParam;

class Actor : public BaseProc {
public:
    enum class StasisFlag {
        _1 = 1,
        _2 = 2,
        _4 = 4,
    };

    Actor();  // FIXME
    ~Actor() override;

    SEAD_RTTI_OVERRIDE(Actor, BaseProc)

    const ActorParam* getParam() const { return mActorParam; }
    const map::MubinIter& getMapObjIter() const { return mMapObjIter; }

    virtual s32 getMaxLife();

    virtual LifeRecoverInfo* getLifeRecoverInfo();

    void emitBasicSigOn();
    void emitBasicSigOff();

    void nullsub_4649();  // Some kind of logging which has been excluded from the build?

    const sead::TypedBitFlag<StasisFlag>& getStasisFlags() const { return mStasisFlags; }

protected:
    /* 0x180 */ u8 TEMP_0x180[0x3D8];  // FIXME
    /* 0x558 */ ai::RootAi* mRootAi;
    /* 0x560 */ void* mASList;   // FIXME
    /* 0x568 */ void* mEffects;  // FIXME
    /* 0x570 */ ActorParam* mActorParam;
    /* 0x578 */ u8 TEMP_0x578[0x648 - 0x578];
    /* 0x648 */ map::MubinIter mMapObjIter;
    /* 0x658 */ u8 TEMP_0x650[0x710 - 0x658];
    // The name could be incorrect.
    /* 0x710 */ sead::TypedBitFlag<StasisFlag> mStasisFlags;
    /* 0x714 */ u8 TEMP_0x714[0x838 - 0x714];  // FIXME
};
KSYS_CHECK_SIZE_NX150(Actor, 0x838);

}  // namespace act

}  // namespace ksys
