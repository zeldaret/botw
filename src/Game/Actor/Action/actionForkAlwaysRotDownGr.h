#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAlwaysRotDownGr : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAlwaysRotDownGr, ksys::act::ai::Action)
public:
    explicit ForkAlwaysRotDownGr(const InitArg& arg);
    ~ForkAlwaysRotDownGr() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mGroundRotAngle_s{};
};

}  // namespace uking::action
