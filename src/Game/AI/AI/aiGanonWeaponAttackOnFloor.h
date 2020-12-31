#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonWeaponAttackOnFloor : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonWeaponAttackOnFloor, ksys::act::ai::Ai)
public:
    explicit GanonWeaponAttackOnFloor(const InitArg& arg);
    ~GanonWeaponAttackOnFloor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mCloseDist_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
