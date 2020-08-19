#pragma once

#include "KingSystem/ActorSystem/actBaseProc.h"

namespace ksys {

namespace act {

class Actor : public BaseProc {
public:
    Actor();  // FIXME
    ~Actor() override;

    SEAD_RTTI_OVERRIDE(Actor, BaseProc)

    void emitBasicSigOn();
    void emitBasicSigOff();
};

}  // namespace act

}  // namespace ksys
