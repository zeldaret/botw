#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossBowChildDeviceBreak : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossBowChildDeviceBreak, ksys::act::ai::Action)
public:
    explicit SiteBossBowChildDeviceBreak(const InitArg& arg);
    ~SiteBossBowChildDeviceBreak() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mReactionTime_s{};
    // static_param at offset 0x28
    const bool* mIsDelete_s{};
};

}  // namespace uking::action
