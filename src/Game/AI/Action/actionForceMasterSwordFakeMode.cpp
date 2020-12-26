#include "Game/AI/Action/actionForceMasterSwordFakeMode.h"

namespace uking::action {

ForceMasterSwordFakeMode::ForceMasterSwordFakeMode(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForceMasterSwordFakeMode::~ForceMasterSwordFakeMode() = default;

bool ForceMasterSwordFakeMode::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceMasterSwordFakeMode::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForceMasterSwordFakeMode::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForceMasterSwordFakeMode::loadParams_() {}

void ForceMasterSwordFakeMode::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
