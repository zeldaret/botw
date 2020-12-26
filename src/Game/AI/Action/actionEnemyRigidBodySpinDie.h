#pragma once

#include "Game/AI/Action/actionEnemyRigidBodyDieBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyRigidBodySpinDie : public EnemyRigidBodyDieBase {
    SEAD_RTTI_OVERRIDE(EnemyRigidBodySpinDie, EnemyRigidBodyDieBase)
public:
    explicit EnemyRigidBodySpinDie(const InitArg& arg);
    ~EnemyRigidBodySpinDie() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    const float* mRiseSpeed_s{};
    // static_param at offset 0x38
    const float* mRotSpeed_s{};
    // static_param at offset 0x40
    const bool* mIsFinishedByBgHit_s{};
    // static_param at offset 0x48
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
