#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WeaponOnetimeUse : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeaponOnetimeUse, ksys::act::ai::Ai)
public:
    explicit WeaponOnetimeUse(const InitArg& arg);
    ~WeaponOnetimeUse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
