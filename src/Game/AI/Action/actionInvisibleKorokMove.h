#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class InvisibleKorokMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(InvisibleKorokMove, ksys::act::ai::Action)
public:
    explicit InvisibleKorokMove(const InitArg& arg);
    ~InvisibleKorokMove() override;

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
};

}  // namespace uking::action
