#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSwarmAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkSwarmAttack, ksys::act::ai::Action)
public:
    explicit ForkSwarmAttack(const InitArg& arg);
    ~ForkSwarmAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAttackIntensity_s{};
    // static_param at offset 0x28
    const bool* mIsAttackOnce_s{};
};

}  // namespace uking::action
