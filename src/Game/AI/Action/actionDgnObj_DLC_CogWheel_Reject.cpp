#include "Game/AI/Action/actionDgnObj_DLC_CogWheel_Reject.h"

namespace uking::action {

DgnObj_DLC_CogWheel_Reject::DgnObj_DLC_CogWheel_Reject(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DgnObj_DLC_CogWheel_Reject::~DgnObj_DLC_CogWheel_Reject() = default;

bool DgnObj_DLC_CogWheel_Reject::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DgnObj_DLC_CogWheel_Reject::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DgnObj_DLC_CogWheel_Reject::leave_() {
    ksys::act::ai::Action::leave_();
}

void DgnObj_DLC_CogWheel_Reject::loadParams_() {}

void DgnObj_DLC_CogWheel_Reject::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
