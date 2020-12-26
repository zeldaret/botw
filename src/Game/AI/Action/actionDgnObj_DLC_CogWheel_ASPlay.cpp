#include "Game/AI/Action/actionDgnObj_DLC_CogWheel_ASPlay.h"

namespace uking::action {

DgnObj_DLC_CogWheel_ASPlay::DgnObj_DLC_CogWheel_ASPlay(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DgnObj_DLC_CogWheel_ASPlay::~DgnObj_DLC_CogWheel_ASPlay() = default;

bool DgnObj_DLC_CogWheel_ASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DgnObj_DLC_CogWheel_ASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DgnObj_DLC_CogWheel_ASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void DgnObj_DLC_CogWheel_ASPlay::loadParams_() {}

void DgnObj_DLC_CogWheel_ASPlay::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
