#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyFortressChatTurnBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EnemyFortressChatTurnBase, ksys::act::ai::Action)
public:
    explicit EnemyFortressChatTurnBase(const InitArg& arg);
    ~EnemyFortressChatTurnBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTryNum_s{};
    // dynamic_param at offset 0x28
    ksys::act::BaseProcLink* mTargetActor_d{};
    // aitree_variable at offset 0x30
    void* mRegistedActorUnit_a{};
};

}  // namespace uking::action
