#include "Game/AI/Action/actionGiantEnemyWalk.h"

namespace uking::action {

GiantEnemyWalk::GiantEnemyWalk(const InitArg& arg) : GiantEnemyWalkWithVibration(arg) {}

GiantEnemyWalk::~GiantEnemyWalk() = default;

bool GiantEnemyWalk::init_(sead::Heap* heap) {
    return GiantEnemyWalkWithVibration::init_(heap);
}

void GiantEnemyWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantEnemyWalkWithVibration::enter_(params);
}

void GiantEnemyWalk::leave_() {
    GiantEnemyWalkWithVibration::leave_();
}

void GiantEnemyWalk::loadParams_() {
    GiantEnemyWalkWithVibration::loadParams_();
}

void GiantEnemyWalk::calc_() {
    GiantEnemyWalkWithVibration::calc_();
}

}  // namespace uking::action
