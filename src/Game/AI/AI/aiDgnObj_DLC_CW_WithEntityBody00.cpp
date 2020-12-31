#include "Game/AI/AI/aiDgnObj_DLC_CW_WithEntityBody00.h"

namespace uking::ai {

DgnObj_DLC_CW_WithEntityBody00::DgnObj_DLC_CW_WithEntityBody00(const InitArg& arg)
    : DgnObj_DLC_CogWheel2(arg) {}

DgnObj_DLC_CW_WithEntityBody00::~DgnObj_DLC_CW_WithEntityBody00() = default;

bool DgnObj_DLC_CW_WithEntityBody00::init_(sead::Heap* heap) {
    return DgnObj_DLC_CogWheel2::init_(heap);
}

void DgnObj_DLC_CW_WithEntityBody00::enter_(ksys::act::ai::InlineParamPack* params) {
    DgnObj_DLC_CogWheel2::enter_(params);
}

void DgnObj_DLC_CW_WithEntityBody00::leave_() {
    DgnObj_DLC_CogWheel2::leave_();
}

void DgnObj_DLC_CW_WithEntityBody00::loadParams_() {
    DgnObj_DLC_CogWheel2::loadParams_();
}

}  // namespace uking::ai
