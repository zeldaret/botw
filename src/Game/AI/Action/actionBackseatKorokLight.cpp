#include "Game/AI/Action/actionBackseatKorokLight.h"

namespace uking::action {

BackseatKorokLight::BackseatKorokLight(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BackseatKorokLight::~BackseatKorokLight() = default;

bool BackseatKorokLight::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BackseatKorokLight::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BackseatKorokLight::leave_() {
    ksys::act::ai::Action::leave_();
}

void BackseatKorokLight::loadParams_() {
    getStaticParam(&mAppearDist_s, "AppearDist");
    getStaticParam(&mDisappearDist_s, "DisappearDist");
    getStaticParam(&mGroundWaitASName_s, "GroundWaitASName");
    getStaticParam(&mGroundAppearASName_s, "GroundAppearASName");
    getStaticParam(&mGroundDisappearASName_s, "GroundDisappearASName");
    getStaticParam(&mFlyWaitASName_s, "FlyWaitASName");
    getStaticParam(&mFlyAppearASName_s, "FlyAppearASName");
    getStaticParam(&mFlyDisappearASName_s, "FlyDisappearASName");
    getMapUnitParam(&mPlacementType_m, "PlacementType");
}

void BackseatKorokLight::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
