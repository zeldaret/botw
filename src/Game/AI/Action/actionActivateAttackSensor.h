#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ActivateAttackSensor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ActivateAttackSensor, ksys::act::ai::Action)
public:
    explicit ActivateAttackSensor(const InitArg& arg);
    ~ActivateAttackSensor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtDamage_s{};
    // static_param at offset 0x28
    const int* mAtPower_s{};
    // static_param at offset 0x30
    const int* mAtPowerReduce_s{};
    // static_param at offset 0x38
    const int* mAtImpact_s{};
    // static_param at offset 0x40
    const int* mAtShieldBreakPower_s{};
    // static_param at offset 0x48
    const int* mAtType_s{};
    // static_param at offset 0x50
    const int* mAtAttr_s{};
    // static_param at offset 0x58
    const int* mAtDirType_s{};
    // static_param at offset 0x60
    const float* mFramesActive_s{};
    // static_param at offset 0x68
    const bool* mIsSuccessFinishCounterEnd_s{};
    // static_param at offset 0x70
    const bool* mIsChangeable_s{};
    // static_param at offset 0x78
    const bool* mUseMapUnitParamForDamage_s{};
    // static_param at offset 0x80
    sead::SafeString mAtkSensorName_s{};
    // map_unit_param at offset 0x90
    const int* mAttackPower_m{};
};

}  // namespace uking::action
