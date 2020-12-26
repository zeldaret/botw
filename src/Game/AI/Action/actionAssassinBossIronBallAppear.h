#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AssassinBossIronBallAppear : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AssassinBossIronBallAppear, ksys::act::ai::Action)
public:
    explicit AssassinBossIronBallAppear(const InitArg& arg);
    ~AssassinBossIronBallAppear() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mIronBallNum_s{};
    // static_param at offset 0x28
    const float* mCreateDist_s{};
    // static_param at offset 0x30
    const float* mBackDist_s{};
    // static_param at offset 0x38
    const float* mTopOffsetY_s{};
    // static_param at offset 0x40
    const float* mBaseOffsetY_s{};
    // static_param at offset 0x48
    const float* mUDLimit_s{};
    // static_param at offset 0x50
    sead::SafeString mIronBallPartsName_s{};
};

}  // namespace uking::action
