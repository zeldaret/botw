#pragma once

#include "Game/AI/Action/actionTurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LookAtTarget : public TurnBase {
    SEAD_RTTI_OVERRIDE(LookAtTarget, TurnBase)
public:
    explicit LookAtTarget(const InitArg& arg);
    ~LookAtTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    sead::SafeString mASKeyName_s{};
};

}  // namespace uking::action
