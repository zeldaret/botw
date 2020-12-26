#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpPlayerToAnchorGimmickReset : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpPlayerToAnchorGimmickReset, ksys::act::ai::Action)
public:
    explicit WarpPlayerToAnchorGimmickReset(const InitArg& arg);
    ~WarpPlayerToAnchorGimmickReset() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mWaitFrameAfterReset_s{};
    // map_unit_param at offset 0x28
    sead::SafeString mAnchorName_m{};
    // map_unit_param at offset 0x38
    sead::SafeString mAnchorUniqueName_m{};
};

}  // namespace uking::action
