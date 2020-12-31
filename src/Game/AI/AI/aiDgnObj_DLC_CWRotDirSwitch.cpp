#include "Game/AI/AI/aiDgnObj_DLC_CWRotDirSwitch.h"

namespace uking::ai {

DgnObj_DLC_CWRotDirSwitch::DgnObj_DLC_CWRotDirSwitch(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DgnObj_DLC_CWRotDirSwitch::~DgnObj_DLC_CWRotDirSwitch() = default;

bool DgnObj_DLC_CWRotDirSwitch::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DgnObj_DLC_CWRotDirSwitch::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DgnObj_DLC_CWRotDirSwitch::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DgnObj_DLC_CWRotDirSwitch::loadParams_() {}

}  // namespace uking::ai
