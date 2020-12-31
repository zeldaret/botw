#include "Game/AI/AI/aiDgnObj_DLC_Faucet.h"

namespace uking::ai {

DgnObj_DLC_Faucet::DgnObj_DLC_Faucet(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DgnObj_DLC_Faucet::~DgnObj_DLC_Faucet() = default;

bool DgnObj_DLC_Faucet::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DgnObj_DLC_Faucet::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DgnObj_DLC_Faucet::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DgnObj_DLC_Faucet::loadParams_() {}

}  // namespace uking::ai
