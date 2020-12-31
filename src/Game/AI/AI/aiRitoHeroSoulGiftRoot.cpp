#include "Game/AI/AI/aiRitoHeroSoulGiftRoot.h"

namespace uking::ai {

RitoHeroSoulGiftRoot::RitoHeroSoulGiftRoot(const InitArg& arg) : HeroSoulGiftRoot(arg) {}

RitoHeroSoulGiftRoot::~RitoHeroSoulGiftRoot() = default;

bool RitoHeroSoulGiftRoot::init_(sead::Heap* heap) {
    return HeroSoulGiftRoot::init_(heap);
}

void RitoHeroSoulGiftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HeroSoulGiftRoot::enter_(params);
}

void RitoHeroSoulGiftRoot::leave_() {
    HeroSoulGiftRoot::leave_();
}

void RitoHeroSoulGiftRoot::loadParams_() {
    HeroSoulGiftRoot::loadParams_();
    getStaticParam(&mActorName_s, "ActorName");
    getStaticParam(&mScale_s, "Scale");
}

}  // namespace uking::ai
