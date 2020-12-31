#include "Game/AI/AI/aiSiteBossArrowRainAttack.h"

namespace uking::ai {

SiteBossArrowRainAttack::SiteBossArrowRainAttack(const InitArg& arg)
    : SiteBossReflectArrowRoot(arg) {}

SiteBossArrowRainAttack::~SiteBossArrowRainAttack() = default;

bool SiteBossArrowRainAttack::init_(sead::Heap* heap) {
    return SiteBossReflectArrowRoot::init_(heap);
}

void SiteBossArrowRainAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossReflectArrowRoot::enter_(params);
}

void SiteBossArrowRainAttack::leave_() {
    SiteBossReflectArrowRoot::leave_();
}

void SiteBossArrowRainAttack::loadParams_() {
    SiteBossReflectArrowRoot::loadParams_();
}

}  // namespace uking::ai
