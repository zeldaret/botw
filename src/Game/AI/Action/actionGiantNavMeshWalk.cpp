#include "Game/AI/Action/actionGiantNavMeshWalk.h"

namespace uking::action {

GiantNavMeshWalk::GiantNavMeshWalk(const InitArg& arg) : GiantNavMeshWalkWithVibration(arg) {}

GiantNavMeshWalk::~GiantNavMeshWalk() = default;

bool GiantNavMeshWalk::init_(sead::Heap* heap) {
    return GiantNavMeshWalkWithVibration::init_(heap);
}

void GiantNavMeshWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantNavMeshWalkWithVibration::enter_(params);
}

void GiantNavMeshWalk::leave_() {
    GiantNavMeshWalkWithVibration::leave_();
}

void GiantNavMeshWalk::loadParams_() {
    GiantNavMeshWalkWithVibration::loadParams_();
}

void GiantNavMeshWalk::calc_() {
    GiantNavMeshWalkWithVibration::calc_();
}

}  // namespace uking::action
