#pragma once

#include "Game/AI/AI/aiHorseFollow.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WolfLinkFollowPlayerRoot : public HorseFollow {
    SEAD_RTTI_OVERRIDE(WolfLinkFollowPlayerRoot, HorseFollow)
public:
    explicit WolfLinkFollowPlayerRoot(const InitArg& arg);
    ~WolfLinkFollowPlayerRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    const float* mLateralDistance_s{};
    // static_param at offset 0xe8
    const float* mAnteriorDistanceStop_s{};
    // static_param at offset 0xf0
    const float* mAnteriorDistanceRun_s{};
    // static_param at offset 0xf8
    const float* mAnteriorDistanceSprint_s{};
};

}  // namespace uking::ai
