#include "Game/AI/Action/actionNavMeshMoveWithAS.h"

namespace uking::action {

NavMeshMoveWithAS::NavMeshMoveWithAS(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshMoveWithAS::~NavMeshMoveWithAS() = default;

bool NavMeshMoveWithAS::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshMoveWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshMoveWithAS::leave_() {
    NavMeshAction::leave_();
}

void NavMeshMoveWithAS::loadParams_() {
    NavMeshAction::loadParams_();
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mASName_s, "ASName");
}

void NavMeshMoveWithAS::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
