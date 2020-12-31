#include "Game/AI/AI/aiDgnObj_DLC_CogWheel_Physics_Ctr.h"

namespace uking::ai {

DgnObj_DLC_CogWheel_Physics_Ctr::DgnObj_DLC_CogWheel_Physics_Ctr(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

DgnObj_DLC_CogWheel_Physics_Ctr::~DgnObj_DLC_CogWheel_Physics_Ctr() = default;

bool DgnObj_DLC_CogWheel_Physics_Ctr::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DgnObj_DLC_CogWheel_Physics_Ctr::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DgnObj_DLC_CogWheel_Physics_Ctr::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DgnObj_DLC_CogWheel_Physics_Ctr::loadParams_() {
    getStaticParam(&mStateRot_s, "StateRot");
}

}  // namespace uking::ai
