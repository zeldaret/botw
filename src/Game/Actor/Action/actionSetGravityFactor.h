#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetGravityFactor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetGravityFactor, ksys::act::ai::Action)
public:
    explicit SetGravityFactor(const InitArg& arg);
    ~SetGravityFactor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mValue_s{};
};

}  // namespace uking::action
