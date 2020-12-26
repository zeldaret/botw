#pragma once

#include "Game/AI/Action/actionEnemyRigidBodyDieBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyRigidBodyDie : public EnemyRigidBodyDieBase {
    SEAD_RTTI_OVERRIDE(EnemyRigidBodyDie, EnemyRigidBodyDieBase)
public:
    explicit EnemyRigidBodyDie(const InitArg& arg);
    ~EnemyRigidBodyDie() override;

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
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
