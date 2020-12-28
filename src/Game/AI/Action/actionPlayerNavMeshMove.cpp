#include "Game/AI/Action/actionPlayerNavMeshMove.h"

namespace uking::action {

PlayerNavMeshMove::PlayerNavMeshMove(const InitArg& arg) : PlayerGuidedMove(arg) {}

void PlayerNavMeshMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerGuidedMove::enter_(params);
}

void PlayerNavMeshMove::leave_() {
    PlayerGuidedMove::leave_();
}

void PlayerNavMeshMove::loadParams_() {
    PlayerGuidedMove::loadParams_();
}

void PlayerNavMeshMove::calc_() {
    PlayerGuidedMove::calc_();
}

}  // namespace uking::action
