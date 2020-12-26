#include "Game/AI/Action/actionSiteBossShootIceSplinter.h"

namespace uking::action {

SiteBossShootIceSplinter::SiteBossShootIceSplinter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossShootIceSplinter::~SiteBossShootIceSplinter() = default;

bool SiteBossShootIceSplinter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossShootIceSplinter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossShootIceSplinter::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossShootIceSplinter::loadParams_() {
    getStaticParam(&mThrowIdxOffset_s, "ThrowIdxOffset");
    getStaticParam(&mInitVelocity_s, "InitVelocity");
    getStaticParam(&mThrowASName_s, "ThrowASName");
    getStaticParam(&mBindNodeName_s, "BindNodeName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void SiteBossShootIceSplinter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
