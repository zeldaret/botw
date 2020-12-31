#pragma once

#include "Game/AI/AI/aiHorseFollow.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnimalFollowTarget : public HorseFollow {
    SEAD_RTTI_OVERRIDE(AnimalFollowTarget, HorseFollow)
public:
    explicit AnimalFollowTarget(const InitArg& arg);
    ~AnimalFollowTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    const int* mUseLocalOffsetType_s{};
};

}  // namespace uking::ai
