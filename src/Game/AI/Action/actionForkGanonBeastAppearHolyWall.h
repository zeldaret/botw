#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkGanonBeastAppearHolyWall : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkGanonBeastAppearHolyWall, ksys::act::ai::Action)
public:
    explicit ForkGanonBeastAppearHolyWall(const InitArg& arg);
    ~ForkGanonBeastAppearHolyWall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mShowDist_s{};
    // static_param at offset 0x28
    const float* mAppearDist_s{};
    // static_param at offset 0x30
    const float* mEffectYOffset_s{};
    // static_param at offset 0x38
    const float* mUiDist_s{};
    // static_param at offset 0x40
    sead::SafeString mKeyName_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mBasePos_s{};
};

}  // namespace uking::action
