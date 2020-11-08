#pragma once

#include "KingSystem/ActorSystem/actBaseProc.h"

namespace ksys {

namespace act {

class LifeRecoverInfo;
class ActorParam;

class Actor : public BaseProc {
public:
    Actor();  // FIXME
    ~Actor() override;

    SEAD_RTTI_OVERRIDE(Actor, BaseProc)

    const ActorParam* getParam() const { return mActorParam; }

    virtual s32 getMaxLife();

    virtual LifeRecoverInfo* getLifeRecoverInfo();

    void emitBasicSigOn();
    void emitBasicSigOff();

    void nullsub_4649();  // Some kind of logging which has been excluded from the build?

protected:
    u8 TEMP1[0x3F4];  // FIXME
    ActorParam* mActorParam;
    u8 TEMP2[0x2C0];  // FIXME
};
KSYS_CHECK_SIZE_NX150(Actor, 0x838);

}  // namespace act

}  // namespace ksys
