#include "Game/Actor/Action/actionGiantEnemyWalk.h"

namespace uking::action {

GiantEnemyWalk::GiantEnemyWalk(const InitArg& arg) : GiantEnemyMoveWithVibration(arg) {}

GiantEnemyWalk::~GiantEnemyWalk() = default;

bool GiantEnemyWalk::init_(sead::Heap* heap) {
    return GiantEnemyMoveWithVibration::init_(heap);
}

void GiantEnemyWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantEnemyMoveWithVibration::enter_(params);
}

void GiantEnemyWalk::leave_() {
    GiantEnemyMoveWithVibration::leave_();
}

void GiantEnemyWalk::loadParams_() {
    GiantEnemyMoveWithVibration::loadParams_();
}

void GiantEnemyWalk::calc_() {
    GiantEnemyMoveWithVibration::calc_();
}

}  // namespace uking::action
