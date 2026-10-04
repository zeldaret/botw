#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackseatKorokLight : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BackseatKorokLight, ksys::act::ai::Action)
public:
    explicit BackseatKorokLight(const InitArg& arg);
    ~BackseatKorokLight() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAppearDist_s{};
    // static_param at offset 0x28
    const float* mDisappearDist_s{};
    // static_param at offset 0x30
    sead::SafeString mGroundWaitASName_s{};
    // static_param at offset 0x40
    sead::SafeString mGroundAppearASName_s{};
    // static_param at offset 0x50
    sead::SafeString mGroundDisappearASName_s{};
    // static_param at offset 0x60
    sead::SafeString mFlyWaitASName_s{};
    // static_param at offset 0x70
    sead::SafeString mFlyAppearASName_s{};
    // static_param at offset 0x80
    sead::SafeString mFlyDisappearASName_s{};
    // map_unit_param at offset 0x90
    sead::SafeString mPlacementType_m{};
};

}  // namespace uking::action
