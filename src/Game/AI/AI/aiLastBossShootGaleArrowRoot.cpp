#include "Game/AI/AI/aiLastBossShootGaleArrowRoot.h"

namespace uking::ai {

LastBossShootGaleArrowRoot::LastBossShootGaleArrowRoot(const InitArg& arg)
    : LastBossShootNormalArrowRoot(arg) {}

LastBossShootGaleArrowRoot::~LastBossShootGaleArrowRoot() = default;

bool LastBossShootGaleArrowRoot::init_(sead::Heap* heap) {
    return LastBossShootNormalArrowRoot::init_(heap);
}

void LastBossShootGaleArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossShootNormalArrowRoot::enter_(params);
}

void LastBossShootGaleArrowRoot::leave_() {
    LastBossShootNormalArrowRoot::leave_();
}

void LastBossShootGaleArrowRoot::loadParams_() {
    LastBossShootNormalArrowRoot::loadParams_();
}

}  // namespace uking::ai
