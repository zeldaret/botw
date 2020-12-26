#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Explode : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Explode, ksys::act::ai::Action)
public:
    explicit Explode(const InitArg& arg);
    ~Explode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mSizeUpTime_s{};
    // static_param at offset 0x28
    const int* mExplodeTime_s{};
    // static_param at offset 0x30
    const int* mAttackIntensity_s{};
    // static_param at offset 0x38
    const bool* mUseDefaultEffect_s{};
    // static_param at offset 0x40
    const bool* mIsDelete_s{};
    // static_param at offset 0x48
    const bool* mIsDamageGuarantee_s{};
    // static_param at offset 0x50
    const bool* mIsVanish_s{};
};

}  // namespace uking::action
