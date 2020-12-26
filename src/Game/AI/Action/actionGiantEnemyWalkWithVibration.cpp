#include "Game/AI/Action/actionGiantEnemyWalkWithVibration.h"

namespace uking::action {

GiantEnemyWalkWithVibration::GiantEnemyWalkWithVibration(const InitArg& arg) : MoveBase(arg) {}

GiantEnemyWalkWithVibration::~GiantEnemyWalkWithVibration() = default;

bool GiantEnemyWalkWithVibration::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void GiantEnemyWalkWithVibration::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

void GiantEnemyWalkWithVibration::leave_() {
    MoveBase::leave_();
}

void GiantEnemyWalkWithVibration::loadParams_() {
    MoveBase::loadParams_();
    getStaticParam(&mVibrationPower_s, "VibrationPower");
}

void GiantEnemyWalkWithVibration::calc_() {
    MoveBase::calc_();
}

}  // namespace uking::action
