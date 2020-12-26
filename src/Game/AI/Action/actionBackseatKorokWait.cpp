#include "Game/AI/Action/actionBackseatKorokWait.h"

namespace uking::action {

BackseatKorokWait::BackseatKorokWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BackseatKorokWait::~BackseatKorokWait() = default;

bool BackseatKorokWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BackseatKorokWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BackseatKorokWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void BackseatKorokWait::loadParams_() {
    getStaticParam(&mAppearDist_s, "AppearDist");
    getStaticParam(&mDisappearDist_s, "DisappearDist");
    getStaticParam(&mWaitASName_s, "WaitASName");
    getStaticParam(&mAppearASName_s, "AppearASName");
    getStaticParam(&mDisappearASName_s, "DisappearASName");
    getMapUnitParam(&mPlacementType_m, "PlacementType");
}

void BackseatKorokWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
