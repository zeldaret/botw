#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCAlert : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCAlert, ksys::act::ai::Ai)
public:
    explicit NPCAlert(const InitArg& arg);
    ~NPCAlert() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mMinReactionTime_s{};
    // static_param at offset 0x40
    const float* mReleaseDist_s{};
    // dynamic_param at offset 0x48
    int* mTerrorLevel_d{};
    // dynamic_param at offset 0x50
    bool* mIsTimeOver_d{};
    // dynamic_param at offset 0x58
    bool* mIsSitting_d{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x68
    ksys::act::BaseProcLink* mTerrorEmitter_d{};
};

}  // namespace uking::ai
