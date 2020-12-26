#include "Game/AI/Action/actionPlayerBeamMove.h"

namespace uking::action {

PlayerBeamMove::PlayerBeamMove(const InitArg& arg) : WindCutter(arg) {}

PlayerBeamMove::~PlayerBeamMove() = default;

bool PlayerBeamMove::init_(sead::Heap* heap) {
    return WindCutter::init_(heap);
}

void PlayerBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    WindCutter::enter_(params);
}

void PlayerBeamMove::leave_() {
    WindCutter::leave_();
}

void PlayerBeamMove::loadParams_() {
    WindCutter::loadParams_();
}

void PlayerBeamMove::calc_() {
    WindCutter::calc_();
}

}  // namespace uking::action
