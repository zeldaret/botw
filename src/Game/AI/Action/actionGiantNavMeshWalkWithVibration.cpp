#include "Game/AI/Action/actionGiantNavMeshWalkWithVibration.h"

namespace uking::action {

GiantNavMeshWalkWithVibration::GiantNavMeshWalkWithVibration(const InitArg& arg)
    : NavMeshAction(arg) {}

GiantNavMeshWalkWithVibration::~GiantNavMeshWalkWithVibration() = default;

bool GiantNavMeshWalkWithVibration::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void GiantNavMeshWalkWithVibration::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void GiantNavMeshWalkWithVibration::leave_() {
    NavMeshAction::leave_();
}

void GiantNavMeshWalkWithVibration::loadParams_() {
    NavMeshAction::loadParams_();
    getStaticParam(&mVibrationPower_s, "VibrationPower");
}

void GiantNavMeshWalkWithVibration::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
