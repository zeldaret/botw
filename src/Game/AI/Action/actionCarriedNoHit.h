#pragma once

#include "Game/AI/Action/actionCarried.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CarriedNoHit : public Carried {
    SEAD_RTTI_OVERRIDE(CarriedNoHit, Carried)
public:
    explicit CarriedNoHit(const InitArg& arg);
    ~CarriedNoHit() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
};

}  // namespace uking::action
