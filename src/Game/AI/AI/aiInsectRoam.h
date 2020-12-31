#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InsectRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(InsectRoam, ksys::act::ai::Ai)
public:
    explicit InsectRoam(const InitArg& arg);
    ~InsectRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTerritoryRadius_s{};
    // static_param at offset 0x40
    const float* mTerritoryRadiusRnd_s{};
    // static_param at offset 0x48
    const float* mMoveDist_s{};
    // static_param at offset 0x50
    const float* mMoveSpeed_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
