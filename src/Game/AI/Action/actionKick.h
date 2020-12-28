#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Kick : public ActionEx {
    SEAD_RTTI_OVERRIDE(Kick, ActionEx)
public:
    explicit Kick(const InitArg& arg);
    ~Kick() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPower_s{};
    // static_param at offset 0x28
    const float* mUpRate_s{};
    // static_param at offset 0x30
    const float* mDirAngle_s{};
    // static_param at offset 0x38
    const float* mCanKickArea_s{};
    // static_param at offset 0x40
    const float* mRotSpeed_s{};
    // dynamic_param at offset 0x48
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action
