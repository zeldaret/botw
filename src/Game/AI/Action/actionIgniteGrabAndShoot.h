#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IgniteGrabAndShoot : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(IgniteGrabAndShoot, ksys::act::ai::Action)
public:
    explicit IgniteGrabAndShoot(const InitArg& arg);
    ~IgniteGrabAndShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpd_s{};
};

}  // namespace uking::action
