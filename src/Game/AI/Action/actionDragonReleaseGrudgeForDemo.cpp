#include "Game/AI/Action/actionDragonReleaseGrudgeForDemo.h"

namespace uking::action {

DragonReleaseGrudgeForDemo::DragonReleaseGrudgeForDemo(const InitArg& arg)
    : DragonPlayASForDemo(arg) {}

DragonReleaseGrudgeForDemo::~DragonReleaseGrudgeForDemo() = default;

bool DragonReleaseGrudgeForDemo::init_(sead::Heap* heap) {
    return DragonPlayASForDemo::init_(heap);
}

void DragonReleaseGrudgeForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonPlayASForDemo::enter_(params);
}

void DragonReleaseGrudgeForDemo::leave_() {
    DragonPlayASForDemo::leave_();
}

void DragonReleaseGrudgeForDemo::loadParams_() {
    DragonPlayASForDemo::loadParams_();
    getStaticParam(&mReleaseTime_s, "ReleaseTime");
    getStaticParam(&mHeadTransSmoothStartFrame_s, "HeadTransSmoothStartFrame");
    getStaticParam(&mHeadTransSmoothEndFrame_s, "HeadTransSmoothEndFrame");
    getStaticParam(&mHeadTransSmoothRate_s, "HeadTransSmoothRate");
    getStaticParam(&mHeadTransSmoothSklRootRate_s, "HeadTransSmoothSklRootRate");
}

void DragonReleaseGrudgeForDemo::calc_() {
    DragonPlayASForDemo::calc_();
}

}  // namespace uking::action
