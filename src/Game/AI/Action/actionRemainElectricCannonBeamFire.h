#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainElectricCannonBeamFire : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainElectricCannonBeamFire, ksys::act::ai::Action)
public:
    explicit RemainElectricCannonBeamFire(const InitArg& arg);
    ~RemainElectricCannonBeamFire() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtkDamage_s{};
    // static_param at offset 0x28
    const int* mMinDamage_s{};
    // dynamic_param at offset 0x30
    bool* mIsProtected_d{};
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mSafePos_d{};
};

}  // namespace uking::action
