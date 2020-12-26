#include "Game/AI/Action/actionOnMUAssignSaveForUsed.h"

namespace uking::action {

OnMUAssignSaveForUsed::OnMUAssignSaveForUsed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OnMUAssignSaveForUsed::~OnMUAssignSaveForUsed() = default;

bool OnMUAssignSaveForUsed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OnMUAssignSaveForUsed::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OnMUAssignSaveForUsed::leave_() {
    ksys::act::ai::Action::leave_();
}

void OnMUAssignSaveForUsed::loadParams_() {}

void OnMUAssignSaveForUsed::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
