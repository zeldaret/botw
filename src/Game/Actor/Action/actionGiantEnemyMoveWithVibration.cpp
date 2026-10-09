#include "Game/Actor/Action/actionGiantEnemyMoveWithVibration.h"

namespace uking::action {

GiantEnemyMoveWithVibration::GiantEnemyMoveWithVibration(const InitArg& arg) : MoveBase(arg) {}

GiantEnemyMoveWithVibration::~GiantEnemyMoveWithVibration() = default;

bool GiantEnemyMoveWithVibration::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void GiantEnemyMoveWithVibration::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

void GiantEnemyMoveWithVibration::leave_() {
    MoveBase::leave_();
}

void GiantEnemyMoveWithVibration::loadParams_() {
    MoveBase::loadParams_();
    getStaticParam(&mVibrationPower_s, "VibrationPower");
}

void GiantEnemyMoveWithVibration::calc_() {
    MoveBase::calc_();
}

}  // namespace uking::action
