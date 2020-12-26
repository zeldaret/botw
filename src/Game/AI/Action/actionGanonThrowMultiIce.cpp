#include "Game/AI/Action/actionGanonThrowMultiIce.h"

namespace uking::action {

GanonThrowMultiIce::GanonThrowMultiIce(const InitArg& arg) : GanonThrowFireBall(arg) {}

GanonThrowMultiIce::~GanonThrowMultiIce() = default;

bool GanonThrowMultiIce::init_(sead::Heap* heap) {
    return GanonThrowFireBall::init_(heap);
}

void GanonThrowMultiIce::enter_(ksys::act::ai::InlineParamPack* params) {
    GanonThrowFireBall::enter_(params);
}

void GanonThrowMultiIce::leave_() {
    GanonThrowFireBall::leave_();
}

void GanonThrowMultiIce::loadParams_() {
    GanonThrowFireBall::loadParams_();
    getStaticParam(&mThrowNumAtSameTiming_s, "ThrowNumAtSameTiming");
    getDynamicParam(&mThrowPartsName1_d, "ThrowPartsName1");
    getDynamicParam(&mThrowPartsName2_d, "ThrowPartsName2");
    getDynamicParam(&mThrowPartsName3_d, "ThrowPartsName3");
    getDynamicParam(&mThrowPartsName4_d, "ThrowPartsName4");
    getDynamicParam(&mThrowPartsName5_d, "ThrowPartsName5");
    getDynamicParam(&mThrowPartsName6_d, "ThrowPartsName6");
    getDynamicParam(&mThrowPartsName7_d, "ThrowPartsName7");
    getDynamicParam(&mThrowPartsName8_d, "ThrowPartsName8");
}

void GanonThrowMultiIce::calc_() {
    GanonThrowFireBall::calc_();
}

}  // namespace uking::action
