#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class KorokTargetMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(KorokTargetMove, ksys::act::ai::Action)
public:
    explicit KorokTargetMove(const InitArg& arg);
    ~KorokTargetMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mSpeed_d{};
    // dynamic_param at offset 0x28
    bool* mIsBezier_d{};
    // dynamic_param at offset 0x30
    sead::Vector3f* mTargetPos_d{};
    // map_unit_param at offset 0x38
    const bool* mIsTargetWarp_m{};
};

}  // namespace uking::action
