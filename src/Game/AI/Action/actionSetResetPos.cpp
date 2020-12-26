#include "Game/AI/Action/actionSetResetPos.h"

namespace uking::action {

SetResetPos::SetResetPos(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetResetPos::~SetResetPos() = default;

bool SetResetPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetResetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetResetPos::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetResetPos::loadParams_() {}

void SetResetPos::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
