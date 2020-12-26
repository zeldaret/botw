#include "Game/AI/Action/actionPlayerDemoAccelerateHorse.h"

namespace uking::action {

PlayerDemoAccelerateHorse::PlayerDemoAccelerateHorse(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PlayerDemoAccelerateHorse::~PlayerDemoAccelerateHorse() = default;

bool PlayerDemoAccelerateHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerDemoAccelerateHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PlayerDemoAccelerateHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayerDemoAccelerateHorse::loadParams_() {
    getStaticParam(&mInputAccelerateFrame_s, "InputAccelerateFrame");
    getStaticParam(&mASName_s, "ASName");
}

void PlayerDemoAccelerateHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
