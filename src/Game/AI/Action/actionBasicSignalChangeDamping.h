#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BasicSignalChangeDamping : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BasicSignalChangeDamping, ksys::act::ai::Action)
public:
    explicit BasicSignalChangeDamping(const InitArg& arg);
    ~BasicSignalChangeDamping() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mLinearDamping_s{};
    // static_param at offset 0x28
    const float* mAngularDamping_s{};
};

}  // namespace uking::action
