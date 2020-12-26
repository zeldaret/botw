#include "Game/AI/Action/actionMsg2CameraKeepState.h"

namespace uking::action {

Msg2CameraKeepState::Msg2CameraKeepState(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Msg2CameraKeepState::~Msg2CameraKeepState() = default;

bool Msg2CameraKeepState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Msg2CameraKeepState::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Msg2CameraKeepState::leave_() {
    ksys::act::ai::Action::leave_();
}

void Msg2CameraKeepState::loadParams_() {}

void Msg2CameraKeepState::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
