#include "Game/AI/AI/aiBlownOff.h"

namespace uking::ai {

BlownOff::BlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool BlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BlownOff::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BlownOff::loadParams_() {
    getStaticParam(&mDrownDepth_s, "DrownDepth");
    getStaticParam(&mIsForceGetUp_s, "IsForceGetUp");
    getStaticParam(&mIsIceBreak_s, "IsIceBreak");
}

}  // namespace uking::ai
