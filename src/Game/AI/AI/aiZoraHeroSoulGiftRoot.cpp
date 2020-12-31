#include "Game/AI/AI/aiZoraHeroSoulGiftRoot.h"

namespace uking::ai {

ZoraHeroSoulGiftRoot::ZoraHeroSoulGiftRoot(const InitArg& arg) : HeroSoulGiftRoot(arg) {}

ZoraHeroSoulGiftRoot::~ZoraHeroSoulGiftRoot() = default;

bool ZoraHeroSoulGiftRoot::init_(sead::Heap* heap) {
    return HeroSoulGiftRoot::init_(heap);
}

void ZoraHeroSoulGiftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HeroSoulGiftRoot::enter_(params);
}

void ZoraHeroSoulGiftRoot::leave_() {
    HeroSoulGiftRoot::leave_();
}

void ZoraHeroSoulGiftRoot::loadParams_() {
    HeroSoulGiftRoot::loadParams_();
}

}  // namespace uking::ai
