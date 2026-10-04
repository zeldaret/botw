#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordAfterImageMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossSwordAfterImageMove, ksys::act::ai::Action)
public:
    explicit SiteBossSwordAfterImageMove(const InitArg& arg);
    ~SiteBossSwordAfterImageMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMoveFrame_s{};
    // map_unit_param at offset 0x28
    const int* mPatternID_m{};
    // aitree_variable at offset 0x30
    void* mSiteBossSwordAfterImageUnit_a{};
};

}  // namespace uking::action
