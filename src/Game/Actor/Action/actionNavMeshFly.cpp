#include "Game/Actor/Action/actionNavMeshFly.h"

namespace uking::action {

NavMeshFly::NavMeshFly(const InitArg& arg) : NavMeshMoveBase(arg) {}

NavMeshFly::~NavMeshFly() = default;

bool NavMeshFly::init_(sead::Heap* heap) {
    return NavMeshMoveBase::init_(heap);
}

void NavMeshFly::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshMoveBase::enter_(params);
}

void NavMeshFly::leave_() {
    NavMeshMoveBase::leave_();
}

void NavMeshFly::loadParams_() {
    NavMeshMoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void NavMeshFly::calc_() {
    NavMeshMoveBase::calc_();
}

}  // namespace uking::action
