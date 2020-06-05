#pragma once

#include "KingSystem/ActorSystem/actBaseProc.h"

namespace ksys {

namespace act {

class Actor : public BaseProc {
public:
    Actor();  // FIXME
    ~Actor() override;

    void emitBasicSigOn();
    void emitBasicSigOff();
};

}  // namespace act

}  // namespace ksys
