#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DropWeapon : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(DropWeapon, OnetimeStopASPlay)
public:
    explicit DropWeapon(const InitArg& arg);
    ~DropWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const int* mWeaponIdx_s{};
    // static_param at offset 0x50
    const float* mWeaponDropSpeedXZ_s{};
    // static_param at offset 0x58
    const float* mWeaponDropSpeedY_s{};
    // static_param at offset 0x60
    const float* mAngleOffsetY_s{};
    // static_param at offset 0x68
    const bool* mChemReset_s{};
};

}  // namespace uking::action
