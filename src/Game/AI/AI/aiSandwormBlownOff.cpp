#include "Game/AI/AI/aiSandwormBlownOff.h"

namespace uking::ai {

SandwormBlownOff::SandwormBlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormBlownOff::~SandwormBlownOff() = default;

bool SandwormBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SandwormBlownOff::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormBlownOff::loadParams_() {
    getStaticParam(&mBlownOffTimer_s, "BlownOffTimer");
}

}  // namespace uking::ai
