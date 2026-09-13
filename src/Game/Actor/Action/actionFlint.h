#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Flint : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Flint, ksys::act::ai::Action)
public:
    explicit Flint(const InitArg& arg);
    ~Flint() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRadius_s{};
    // static_param at offset 0x28
    const float* mLife_s{};
    // static_param at offset 0x30
    const bool* mSetDelete_s{};
};

}  // namespace uking::action
