#include "Game/AI/AI/aiGerudoHeroSoulGiftRoot.h"

namespace uking::ai {

GerudoHeroSoulGiftRoot::GerudoHeroSoulGiftRoot(const InitArg& arg) : HeroSoulGiftRoot(arg) {}

GerudoHeroSoulGiftRoot::~GerudoHeroSoulGiftRoot() = default;

bool GerudoHeroSoulGiftRoot::init_(sead::Heap* heap) {
    return HeroSoulGiftRoot::init_(heap);
}

void GerudoHeroSoulGiftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HeroSoulGiftRoot::enter_(params);
}

void GerudoHeroSoulGiftRoot::leave_() {
    HeroSoulGiftRoot::leave_();
}

void GerudoHeroSoulGiftRoot::loadParams_() {
    HeroSoulGiftRoot::loadParams_();
    getStaticParam(&mMaxLength_s, "MaxLength");
}

}  // namespace uking::ai
