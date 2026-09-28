#include "Game/Actor/Action/actionGiantNavMeshWalk.h"

namespace uking::action {

GiantNavMeshWalk::GiantNavMeshWalk(const InitArg& arg) : GiantNavMeshMoveWithVibration(arg) {}

GiantNavMeshWalk::~GiantNavMeshWalk() = default;

bool GiantNavMeshWalk::init_(sead::Heap* heap) {
    return GiantNavMeshMoveWithVibration::init_(heap);
}

void GiantNavMeshWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantNavMeshMoveWithVibration::enter_(params);
}

void GiantNavMeshWalk::leave_() {
    GiantNavMeshMoveWithVibration::leave_();
}

void GiantNavMeshWalk::loadParams_() {
    GiantNavMeshMoveWithVibration::loadParams_();
}

void GiantNavMeshWalk::calc_() {
    GiantNavMeshMoveWithVibration::calc_();
}

}  // namespace uking::action
