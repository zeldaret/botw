#pragma once

#include "Game/AI/AI/aiHeroSoulGiftRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GerudoHeroSoulGiftRoot : public HeroSoulGiftRoot {
    SEAD_RTTI_OVERRIDE(GerudoHeroSoulGiftRoot, HeroSoulGiftRoot)
public:
    explicit GerudoHeroSoulGiftRoot(const InitArg& arg);
    ~GerudoHeroSoulGiftRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const float* mMaxLength_s{};
};

}  // namespace uking::ai
