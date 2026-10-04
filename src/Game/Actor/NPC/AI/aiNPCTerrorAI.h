#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCTerrorAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCTerrorAI, ksys::act::ai::Ai)
public:
    explicit NPCTerrorAI(const InitArg& arg);
    ~NPCTerrorAI() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mTerrorEndTime_s{};
    // dynamic_param at offset 0x40
    int* mTerrorLayer_d{};
    // dynamic_param at offset 0x48
    float* mTerrorLevel_d{};
    // dynamic_param at offset 0x50
    bool* mIsReturnFromDemo_d{};
    // dynamic_param at offset 0x58
    bool* mIsTimeOver_d{};
    // dynamic_param at offset 0x60
    bool* mIsNeedUnEquipWeapon_d{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetVel_d{};
    // dynamic_param at offset 0x78
    ksys::act::BaseProcLink* mTerrorEmitter_d{};
};

}  // namespace uking::ai
