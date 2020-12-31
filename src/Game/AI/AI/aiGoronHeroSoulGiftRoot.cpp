#include "Game/AI/AI/aiGoronHeroSoulGiftRoot.h"

namespace uking::ai {

GoronHeroSoulGiftRoot::GoronHeroSoulGiftRoot(const InitArg& arg) : HeroSoulGiftRoot(arg) {}

GoronHeroSoulGiftRoot::~GoronHeroSoulGiftRoot() = default;

bool GoronHeroSoulGiftRoot::init_(sead::Heap* heap) {
    return HeroSoulGiftRoot::init_(heap);
}

void GoronHeroSoulGiftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HeroSoulGiftRoot::enter_(params);
}

void GoronHeroSoulGiftRoot::leave_() {
    HeroSoulGiftRoot::leave_();
}

void GoronHeroSoulGiftRoot::loadParams_() {
    HeroSoulGiftRoot::loadParams_();
}

}  // namespace uking::ai
