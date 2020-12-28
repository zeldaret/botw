#include "Game/AI/Action/actionResetPlayerPullSwordStartLife.h"

namespace uking::action {

ResetPlayerPullSwordStartLife::ResetPlayerPullSwordStartLife(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ResetPlayerPullSwordStartLife::~ResetPlayerPullSwordStartLife() = default;

bool ResetPlayerPullSwordStartLife::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ResetPlayerPullSwordStartLife::loadParams_() {}

}  // namespace uking::action
