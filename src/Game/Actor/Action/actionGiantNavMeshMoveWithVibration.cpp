#include "Game/Actor/Action/actionGiantNavMeshMoveWithVibration.h"

namespace uking::action {

GiantNavMeshMoveWithVibration::GiantNavMeshMoveWithVibration(const InitArg& arg)
    : NavMeshMoveBase(arg) {}

GiantNavMeshMoveWithVibration::~GiantNavMeshMoveWithVibration() = default;

bool GiantNavMeshMoveWithVibration::init_(sead::Heap* heap) {
    return NavMeshMoveBase::init_(heap);
}

void GiantNavMeshMoveWithVibration::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshMoveBase::enter_(params);
}

void GiantNavMeshMoveWithVibration::leave_() {
    NavMeshMoveBase::leave_();
}

void GiantNavMeshMoveWithVibration::loadParams_() {
    NavMeshMoveBase::loadParams_();
    getStaticParam(&mVibrationPower_s, "VibrationPower");
}

void GiantNavMeshMoveWithVibration::calc_() {
    NavMeshMoveBase::calc_();
}

}  // namespace uking::action
