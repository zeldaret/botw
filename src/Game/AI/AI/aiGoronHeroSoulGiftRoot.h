#pragma once

#include "Game/AI/AI/aiHeroSoulGiftRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GoronHeroSoulGiftRoot : public HeroSoulGiftRoot {
    SEAD_RTTI_OVERRIDE(GoronHeroSoulGiftRoot, HeroSoulGiftRoot)
public:
    explicit GoronHeroSoulGiftRoot(const InitArg& arg);
    ~GoronHeroSoulGiftRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
