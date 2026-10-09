#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyFortressChatLookBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EnemyFortressChatLookBase, ksys::act::ai::Action)
public:
    explicit EnemyFortressChatLookBase(const InitArg& arg);
    ~EnemyFortressChatLookBase() override;

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
