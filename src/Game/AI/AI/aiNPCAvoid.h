#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCAvoid : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCAvoid, ksys::act::ai::Ai)
public:
    explicit NPCAvoid(const InitArg& arg);
    ~NPCAvoid() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mTargetTerrorLevel_s{};
    // static_param at offset 0x40
    const int* mReleaseCrouchTime_s{};
    // dynamic_param at offset 0x48
    int* mTerrorLevel_d{};
    // dynamic_param at offset 0x50
    int* mTerrorLayer_d{};
    // dynamic_param at offset 0x58
    bool* mIsReturnFromDemo_d{};
    // dynamic_param at offset 0x60
    bool* mIsNeedUnEquipWeapon_d{};
    // dynamic_param at offset 0x68
    bool* mIsSitting_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetVel_d{};
    // dynamic_param at offset 0x80
    ksys::act::BaseProcLink* mTerrorEmitter_d{};
};

}  // namespace uking::ai
