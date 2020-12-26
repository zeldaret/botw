#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ApplyMoveImpulse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ApplyMoveImpulse, ksys::act::ai::Action)
public:
    explicit ApplyMoveImpulse(const InitArg& arg);
    ~ApplyMoveImpulse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mFellImpRate_s{};
    // static_param at offset 0x28
    const float* mFellRotRate_s{};
};

}  // namespace uking::action
