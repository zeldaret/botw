#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TeleportBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TeleportBase, ksys::act::ai::Action)
public:
    explicit TeleportBase(const InitArg& arg);
    ~TeleportBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWaitTime_s{};
    // static_param at offset 0x28
    const int* mTimeRand_s{};
    // static_param at offset 0x30
    const bool* mIsUseChangePos_s{};
    // static_param at offset 0x38
    const bool* mIsLifeGageKeep_s{};
    // static_param at offset 0x40
    sead::SafeString mEffectName_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
