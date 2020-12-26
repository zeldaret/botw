#include "Game/AI/Action/actionPlayerSetWakeUpMtx.h"

namespace uking::action {

PlayerSetWakeUpMtx::PlayerSetWakeUpMtx(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PlayerSetWakeUpMtx::~PlayerSetWakeUpMtx() = default;

bool PlayerSetWakeUpMtx::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerSetWakeUpMtx::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PlayerSetWakeUpMtx::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayerSetWakeUpMtx::loadParams_() {}

void PlayerSetWakeUpMtx::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
