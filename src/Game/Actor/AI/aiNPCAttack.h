#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCAttack, ksys::act::ai::Ai)
public:
    explicit NPCAttack(const InitArg& arg);
    ~NPCAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mActionBaseTime_s{};
    // static_param at offset 0x40
    const int* mActionTimePlay_s{};
    // static_param at offset 0x48
    const int* mActionRate_s{};
    // static_param at offset 0x50
    const int* mAttackRate_s{};
    // static_param at offset 0x58
    const int* mAttackModeTime_s{};
    // static_param at offset 0x60
    const int* mGuardModeTime_s{};
    // static_param at offset 0x68
    const int* mEnemyChanceTime_s{};
    // dynamic_param at offset 0x70
    float* mTerrorLevel_d{};
    // dynamic_param at offset 0x78
    bool* mIsBattleStart_d{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x88
    ksys::act::BaseProcLink* mEnemyLink_d{};
};

}  // namespace uking::ai
