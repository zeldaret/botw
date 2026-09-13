#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkCapsuleWindFollow : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkCapsuleWindFollow, ksys::act::ai::Action)
public:
    explicit ForkCapsuleWindFollow(const InitArg& arg);
    ~ForkCapsuleWindFollow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRadius_s{};
    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    const float* mLength_s{};
    // static_param at offset 0x38
    const sead::Vector3f* mDir_s{};
};

}  // namespace uking::action
