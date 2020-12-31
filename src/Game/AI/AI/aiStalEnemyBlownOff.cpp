#include "Game/AI/AI/aiStalEnemyBlownOff.h"

namespace uking::ai {

StalEnemyBlownOff::StalEnemyBlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalEnemyBlownOff::~StalEnemyBlownOff() = default;

bool StalEnemyBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalEnemyBlownOff::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalEnemyBlownOff::loadParams_() {
    getStaticParam(&mDrownDepth_s, "DrownDepth");
}

}  // namespace uking::ai
