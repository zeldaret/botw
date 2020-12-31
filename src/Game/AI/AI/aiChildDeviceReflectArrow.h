#pragma once

#include "Game/AI/AI/aiWithoutWeaponArrow.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChildDeviceReflectArrow : public WithoutWeaponArrow {
    SEAD_RTTI_OVERRIDE(ChildDeviceReflectArrow, WithoutWeaponArrow)
public:
    explicit ChildDeviceReflectArrow(const InitArg& arg);
    ~ChildDeviceReflectArrow() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x140
    const int* mReflectCountMax_s{};
    // static_param at offset 0x148
    const float* mReflectAimSpeed_s{};
    // static_param at offset 0x150
    const float* mReflectAccel_s{};
};

}  // namespace uking::ai
