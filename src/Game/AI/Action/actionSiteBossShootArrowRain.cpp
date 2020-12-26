#include "Game/AI/Action/actionSiteBossShootArrowRain.h"

namespace uking::action {

SiteBossShootArrowRain::SiteBossShootArrowRain(const InitArg& arg)
    : SiteBossShootNormalArrow(arg) {}

SiteBossShootArrowRain::~SiteBossShootArrowRain() = default;

bool SiteBossShootArrowRain::init_(sead::Heap* heap) {
    return SiteBossShootNormalArrow::init_(heap);
}

void SiteBossShootArrowRain::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossShootNormalArrow::enter_(params);
}

void SiteBossShootArrowRain::leave_() {
    SiteBossShootNormalArrow::leave_();
}

void SiteBossShootArrowRain::loadParams_() {
    SiteBossShootNormalArrow::loadParams_();
    getStaticParam(&mArrowType_s, "ArrowType");
}

void SiteBossShootArrowRain::calc_() {
    SiteBossShootNormalArrow::calc_();
}

}  // namespace uking::action
