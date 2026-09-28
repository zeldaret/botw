#include "Game/Actor/Action/actionNavMeshBattleWalk.h"

namespace uking::action {

NavMeshBattleWalk::NavMeshBattleWalk(const InitArg& arg) : NavMeshMoveBase(arg) {}

bool NavMeshBattleWalk::init_(sead::Heap* heap) {
    return NavMeshMoveBase::init_(heap);
}

void NavMeshBattleWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshMoveBase::enter_(params);
}

void NavMeshBattleWalk::leave_() {
    NavMeshMoveBase::leave_();
}

void NavMeshBattleWalk::loadParams_() {
    NavMeshMoveBase::loadParams_();
}

void NavMeshBattleWalk::calc_() {
    NavMeshMoveBase::calc_();
}

}  // namespace uking::action
