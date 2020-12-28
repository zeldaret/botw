#include "Game/AI/Action/actionNavMeshMoveWithAS.h"

namespace uking::action {

NavMeshMoveWithAS::NavMeshMoveWithAS(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshMoveWithAS::~NavMeshMoveWithAS() = default;

bool NavMeshMoveWithAS::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshMoveWithAS::loadParams_() {
    NavMeshAction::loadParams_();
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
