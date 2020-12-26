#pragma once

#include "Game/AI/Action/actionEnemyRigidBodyDieBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyRigidBodyFreeFallDie : public EnemyRigidBodyDieBase {
    SEAD_RTTI_OVERRIDE(EnemyRigidBodyFreeFallDie, EnemyRigidBodyDieBase)
public:
    explicit EnemyRigidBodyFreeFallDie(const InitArg& arg);
    ~EnemyRigidBodyFreeFallDie() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x28
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
