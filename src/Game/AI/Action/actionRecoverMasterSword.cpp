#include "Game/AI/Action/actionRecoverMasterSword.h"

namespace uking::action {

RecoverMasterSword::RecoverMasterSword(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RecoverMasterSword::~RecoverMasterSword() = default;

bool RecoverMasterSword::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RecoverMasterSword::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RecoverMasterSword::leave_() {
    ksys::act::ai::Action::leave_();
}

void RecoverMasterSword::loadParams_() {}

void RecoverMasterSword::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
