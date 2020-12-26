#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkStalEnemyForceDamage : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkStalEnemyForceDamage, ksys::act::ai::Action)
public:
    explicit ForkStalEnemyForceDamage(const InitArg& arg);
    ~ForkStalEnemyForceDamage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mDamage_s{};
    // static_param at offset 0x28
    const int* mASTrigType_s{};
    // static_param at offset 0x30
    const int* mDamageType_s{};
    // static_param at offset 0x38
    const int* mDamageAttr_s{};
    // static_param at offset 0x40
    const float* mLifeRate_s{};
};

}  // namespace uking::action
