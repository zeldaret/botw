#include "Game/AI/Action/actionMsg2CameraReset.h"

namespace uking::action {

Msg2CameraReset::Msg2CameraReset(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Msg2CameraReset::~Msg2CameraReset() = default;

bool Msg2CameraReset::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Msg2CameraReset::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Msg2CameraReset::leave_() {
    ksys::act::ai::Action::leave_();
}

void Msg2CameraReset::loadParams_() {}

void Msg2CameraReset::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
