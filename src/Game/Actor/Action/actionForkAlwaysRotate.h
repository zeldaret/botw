#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAlwaysRotate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAlwaysRotate, ksys::act::ai::Action)
public:
    explicit ForkAlwaysRotate(const InitArg& arg);
    ~ForkAlwaysRotate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpd_s{};
    // static_param at offset 0x28
    const bool* mOnEndForceStop_s{};
    // static_param at offset 0x30
    const sead::Vector3f* mRotAxis_s{};
};

}  // namespace uking::action
