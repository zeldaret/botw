#include "Game/AI/Action/actionTeleportTargetFrontInAir.h"

namespace uking::action {

TeleportTargetFrontInAir::TeleportTargetFrontInAir(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

TeleportTargetFrontInAir::~TeleportTargetFrontInAir() = default;

bool TeleportTargetFrontInAir::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TeleportTargetFrontInAir::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TeleportTargetFrontInAir::leave_() {
    ksys::act::ai::Action::leave_();
}

void TeleportTargetFrontInAir::loadParams_() {
    getStaticParam(&mDistMin_s, "DistMin");
    getStaticParam(&mDistMax_s, "DistMax");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getStaticParam(&mTerritoryArea_s, "TerritoryArea");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
}

void TeleportTargetFrontInAir::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
