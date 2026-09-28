#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossSwordWhirlSlashChargeBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossSwordWhirlSlashChargeBase, ksys::act::ai::Action)
public:
    explicit LastBossSwordWhirlSlashChargeBase(const InitArg& arg);
    ~LastBossSwordWhirlSlashChargeBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mChargeTime_s{};
    // static_param at offset 0x28
    const float* mInitSpeed_s{};
    // dynamic_param at offset 0x30
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
