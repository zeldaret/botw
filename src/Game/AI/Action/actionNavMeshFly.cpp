#include "Game/AI/Action/actionNavMeshFly.h"

namespace uking::action {

NavMeshFly::NavMeshFly(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshFly::~NavMeshFly() = default;

bool NavMeshFly::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshFly::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshFly::leave_() {
    NavMeshAction::leave_();
}

void NavMeshFly::loadParams_() {
    NavMeshAction::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void NavMeshFly::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
