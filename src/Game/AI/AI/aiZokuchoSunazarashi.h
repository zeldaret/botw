#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ZokuchoSunazarashi : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ZokuchoSunazarashi, ksys::act::ai::Ai)
public:
    explicit ZokuchoSunazarashi(const InitArg& arg);
    ~ZokuchoSunazarashi() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mPlayerLostDis_s{};
    // static_param at offset 0x40
    const float* mLeadPlayerAngle_s{};
    // static_param at offset 0x48
    const float* mMoveTargetDist_s{};
    // static_param at offset 0x50
    const float* mStopMoveDist_s{};
    // static_param at offset 0x58
    const float* mStayAwayDist_s{};
};

}  // namespace uking::ai
