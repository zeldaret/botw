#include "Game/AI/Action/actionPlayerReleaseMasterSowrd.h"

namespace uking::action {

PlayerReleaseMasterSowrd::PlayerReleaseMasterSowrd(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PlayerReleaseMasterSowrd::~PlayerReleaseMasterSowrd() = default;

bool PlayerReleaseMasterSowrd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerReleaseMasterSowrd::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PlayerReleaseMasterSowrd::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayerReleaseMasterSowrd::loadParams_() {}

void PlayerReleaseMasterSowrd::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
