#include "Game/AI/Action/actionSetPlayerDrawingSword.h"

namespace uking::action {

SetPlayerDrawingSword::SetPlayerDrawingSword(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetPlayerDrawingSword::~SetPlayerDrawingSword() = default;

bool SetPlayerDrawingSword::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetPlayerDrawingSword::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetPlayerDrawingSword::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetPlayerDrawingSword::loadParams_() {}

void SetPlayerDrawingSword::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
