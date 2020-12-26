#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyFortressChatTalk : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EnemyFortressChatTalk, ksys::act::ai::Action)
public:
    explicit EnemyFortressChatTalk(const InitArg& arg);
    ~EnemyFortressChatTalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTryNum_s{};
    // static_param at offset 0x28
    const int* mTimeOut_s{};
    // dynamic_param at offset 0x30
    ksys::act::BaseProcLink* mTargetActor_d{};
    // aitree_variable at offset 0x38
    void* mRegistedActorUnit_a{};
};

}  // namespace uking::action
