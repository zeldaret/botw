#include "Game/Actor/Action/actionNavMeshMoveWithAS.h"

namespace uking::action {

NavMeshMoveWithAS::NavMeshMoveWithAS(const InitArg& arg) : NavMeshMoveBase(arg) {}

NavMeshMoveWithAS::~NavMeshMoveWithAS() = default;

bool NavMeshMoveWithAS::init_(sead::Heap* heap) {
    return NavMeshMoveBase::init_(heap);
}

void NavMeshMoveWithAS::loadParams_() {
    NavMeshMoveBase::loadParams_();
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
