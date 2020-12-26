#include "Game/AI/Action/actionPlayerCleaningAround.h"

namespace uking::action {

PlayerCleaningAround::PlayerCleaningAround(const InitArg& arg) : PlayerAction(arg) {}

PlayerCleaningAround::~PlayerCleaningAround() = default;

bool PlayerCleaningAround::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerCleaningAround::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCleaningAround::leave_() {
    PlayerAction::leave_();
}

void PlayerCleaningAround::loadParams_() {
    getStaticParam(&mCleaningTime_s, "CleaningTime");
}

void PlayerCleaningAround::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
