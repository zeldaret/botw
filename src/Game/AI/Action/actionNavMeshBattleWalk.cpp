#include "Game/AI/Action/actionNavMeshBattleWalk.h"

namespace uking::action {

NavMeshBattleWalk::NavMeshBattleWalk(const InitArg& arg) : NavMeshAction(arg) {}

bool NavMeshBattleWalk::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshBattleWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshBattleWalk::leave_() {
    NavMeshAction::leave_();
}

void NavMeshBattleWalk::loadParams_() {
    NavMeshAction::loadParams_();
}

void NavMeshBattleWalk::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
