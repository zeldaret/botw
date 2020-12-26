#pragma once

#include "Game/AI/Action/actionGiantPunchAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantPunchWithAddEntitySensor : public GiantPunchAttack {
    SEAD_RTTI_OVERRIDE(GiantPunchWithAddEntitySensor, GiantPunchAttack)
public:
    explicit GiantPunchWithAddEntitySensor(const InitArg& arg);
    ~GiantPunchWithAddEntitySensor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
