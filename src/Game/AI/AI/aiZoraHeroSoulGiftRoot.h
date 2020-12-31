#pragma once

#include "Game/AI/AI/aiHeroSoulGiftRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ZoraHeroSoulGiftRoot : public HeroSoulGiftRoot {
    SEAD_RTTI_OVERRIDE(ZoraHeroSoulGiftRoot, HeroSoulGiftRoot)
public:
    explicit ZoraHeroSoulGiftRoot(const InitArg& arg);
    ~ZoraHeroSoulGiftRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
