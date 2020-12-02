#pragma once

#include <prim/seadTypedBitFlag.h>
#include "KingSystem/ActorSystem/actBaseProc.h"

namespace ksys {

namespace act {

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

    virtual s32 getMaxLife();

    virtual LifeRecoverInfo* getLifeRecoverInfo();

    void emitBasicSigOn();
    void emitBasicSigOff();

    void nullsub_4649();  // Some kind of logging which has been excluded from the build?

    const sead::TypedBitFlag<StasisFlag>& getStasisFlags() const { return mStasisFlags; }

protected:
    /* 0x008 */ u8 TEMP_0x008[0x3F4];  // FIXME
    /* 0x570 */ ActorParam* mActorParam;
    /* 0x578 */ u8 TEMP_0x578[0x710 - 0x578];
    // The name could be incorrect.
    /* 0x710 */ sead::TypedBitFlag<StasisFlag> mStasisFlags;
    /* 0x714 */ u8 TEMP_0x714[0x838 - 0x714];  // FIXME
};
KSYS_CHECK_SIZE_NX150(Actor, 0x838);

}  // namespace act

}  // namespace ksys
