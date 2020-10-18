#pragma once

#include "KingSystem/ActorSystem/actBaseProc.h"
#include "actLifeRecoveryInfo.h"

namespace ksys::res {
class GParamList;
}

namespace ksys {

namespace act {

class ActorParam__Data;

class Actor : public BaseProc {
public:
    Actor();  // FIXME
    ~Actor() override;

    SEAD_RTTI_OVERRIDE(Actor, BaseProc)

    virtual ksys::act::LifeRecoverInfo* getLifeRecoverInfo();

    void emitBasicSigOn();
    void emitBasicSigOff();

    void nullsub_4649();  // Some kind of logging which has been excluded from the build?

    u8 TEMP1[0x3F4];  // FIXME
    ActorParam__Data* mActorParam;
    u8 TEMP2[0x2C0];  // FIXME
};
KSYS_CHECK_SIZE_NX150(Actor, 0x838);

}  // namespace act

}  // namespace ksys
