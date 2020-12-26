#pragma once

#include "Game/AI/Action/actionMoveByAnimeDriven.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmDrivenMoveAttack : public MoveByAnimeDriven {
    SEAD_RTTI_OVERRIDE(AnmDrivenMoveAttack, MoveByAnimeDriven)
public:
    explicit AnmDrivenMoveAttack(const InitArg& arg);
    ~AnmDrivenMoveAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x58
    const int* mWeaponIdx_s{};
    // static_param at offset 0x60
    const float* mJustAvoidDist_s{};
    // static_param at offset 0x68
    const bool* mIsForceGuardBreak_s{};
};

}  // namespace uking::action
