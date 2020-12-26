#include "Game/AI/Action/actionArmorBindAction.h"

namespace uking::action {

ArmorBindAction::ArmorBindAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ArmorBindAction::~ArmorBindAction() = default;

bool ArmorBindAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ArmorBindAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ArmorBindAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void ArmorBindAction::loadParams_() {}

void ArmorBindAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
