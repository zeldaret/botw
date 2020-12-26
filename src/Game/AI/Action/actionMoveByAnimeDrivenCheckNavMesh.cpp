#include "Game/AI/Action/actionMoveByAnimeDrivenCheckNavMesh.h"

namespace uking::action {

MoveByAnimeDrivenCheckNavMesh::MoveByAnimeDrivenCheckNavMesh(const InitArg& arg)
    : MoveByAnimeDriven(arg) {}

MoveByAnimeDrivenCheckNavMesh::~MoveByAnimeDrivenCheckNavMesh() = default;

bool MoveByAnimeDrivenCheckNavMesh::init_(sead::Heap* heap) {
    return MoveByAnimeDriven::init_(heap);
}

void MoveByAnimeDrivenCheckNavMesh::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveByAnimeDriven::enter_(params);
}

void MoveByAnimeDrivenCheckNavMesh::leave_() {
    MoveByAnimeDriven::leave_();
}

void MoveByAnimeDrivenCheckNavMesh::loadParams_() {
    MoveByAnimeDriven::loadParams_();
}

void MoveByAnimeDrivenCheckNavMesh::calc_() {
    MoveByAnimeDriven::calc_();
}

}  // namespace uking::action
