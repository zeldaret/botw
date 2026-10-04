#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AmbushableWeaponShoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AmbushableWeaponShoot, ksys::act::ai::Ai)
public:
    explicit AmbushableWeaponShoot(const InitArg& arg);
    ~AmbushableWeaponShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
