#include "Game/AI/Action/actionShootingStarBrightTower.h"

namespace uking::action {

ShootingStarBrightTower::ShootingStarBrightTower(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShootingStarBrightTower::~ShootingStarBrightTower() = default;

bool ShootingStarBrightTower::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShootingStarBrightTower::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ShootingStarBrightTower::leave_() {
    ksys::act::ai::Action::leave_();
}

void ShootingStarBrightTower::loadParams_() {
    getStaticParam(&mDisappearDistance_s, "DisappearDistance");
    getDynamicParam(&mHitGroundAngle_d, "HitGroundAngle");
}

void ShootingStarBrightTower::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
