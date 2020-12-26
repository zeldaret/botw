#include "Game/AI/Action/actionDgnObj_DLC_CWRotDirSwitchOff.h"

namespace uking::action {

DgnObj_DLC_CWRotDirSwitchOff::DgnObj_DLC_CWRotDirSwitchOff(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DgnObj_DLC_CWRotDirSwitchOff::~DgnObj_DLC_CWRotDirSwitchOff() = default;

bool DgnObj_DLC_CWRotDirSwitchOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DgnObj_DLC_CWRotDirSwitchOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DgnObj_DLC_CWRotDirSwitchOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void DgnObj_DLC_CWRotDirSwitchOff::loadParams_() {}

void DgnObj_DLC_CWRotDirSwitchOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
