#include "Game/AI/Action/actionMsg2CameraResetNoConnect.h"

namespace uking::action {

Msg2CameraResetNoConnect::Msg2CameraResetNoConnect(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

Msg2CameraResetNoConnect::~Msg2CameraResetNoConnect() = default;

bool Msg2CameraResetNoConnect::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Msg2CameraResetNoConnect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Msg2CameraResetNoConnect::leave_() {
    ksys::act::ai::Action::leave_();
}

void Msg2CameraResetNoConnect::loadParams_() {}

void Msg2CameraResetNoConnect::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
