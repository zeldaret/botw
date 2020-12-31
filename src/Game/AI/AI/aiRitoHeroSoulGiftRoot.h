#pragma once

#include "Game/AI/AI/aiHeroSoulGiftRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RitoHeroSoulGiftRoot : public HeroSoulGiftRoot {
    SEAD_RTTI_OVERRIDE(RitoHeroSoulGiftRoot, HeroSoulGiftRoot)
public:
    explicit RitoHeroSoulGiftRoot(const InitArg& arg);
    ~RitoHeroSoulGiftRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    sead::SafeString mActorName_s{};
    // static_param at offset 0xa0
    const sead::Vector3f* mScale_s{};
};

}  // namespace uking::ai
