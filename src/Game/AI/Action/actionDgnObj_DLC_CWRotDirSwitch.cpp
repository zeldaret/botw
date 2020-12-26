#include "Game/AI/Action/actionDgnObj_DLC_CWRotDirSwitch.h"

namespace uking::action {

DgnObj_DLC_CWRotDirSwitch::DgnObj_DLC_CWRotDirSwitch(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DgnObj_DLC_CWRotDirSwitch::~DgnObj_DLC_CWRotDirSwitch() = default;

bool DgnObj_DLC_CWRotDirSwitch::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DgnObj_DLC_CWRotDirSwitch::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DgnObj_DLC_CWRotDirSwitch::leave_() {
    ksys::act::ai::Action::leave_();
}

void DgnObj_DLC_CWRotDirSwitch::loadParams_() {}

void DgnObj_DLC_CWRotDirSwitch::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
