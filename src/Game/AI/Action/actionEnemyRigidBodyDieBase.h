#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyRigidBodyDieBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EnemyRigidBodyDieBase, ksys::act::ai::Action)
public:
    explicit EnemyRigidBodyDieBase(const InitArg& arg);
    ~EnemyRigidBodyDieBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    sead::Vector3f* mForceSetDropPos_a{};
};

}  // namespace uking::action
