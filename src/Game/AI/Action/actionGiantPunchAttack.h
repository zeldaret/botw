#pragma once

#include "Game/AI/Action/actionPunchAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantPunchAttack : public PunchAttack {
    SEAD_RTTI_OVERRIDE(GiantPunchAttack, PunchAttack)
public:
    explicit GiantPunchAttack(const InitArg& arg);
    ~GiantPunchAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd0
    sead::SafeString mCoBodyName_s{};
};

}  // namespace uking::action
