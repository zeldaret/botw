#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackseatKorokWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BackseatKorokWait, ksys::act::ai::Action)
public:
    explicit BackseatKorokWait(const InitArg& arg);
    ~BackseatKorokWait() override;

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
    sead::SafeString mWaitASName_s{};
    // static_param at offset 0x40
    sead::SafeString mAppearASName_s{};
    // static_param at offset 0x50
    sead::SafeString mDisappearASName_s{};
    // map_unit_param at offset 0x60
    sead::SafeString mPlacementType_m{};
};

}  // namespace uking::action
