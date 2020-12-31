#include "Game/AI/AI/aiStalEnemyGrabShootOwnPart.h"

namespace uking::ai {

StalEnemyGrabShootOwnPart::StalEnemyGrabShootOwnPart(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalEnemyGrabShootOwnPart::~StalEnemyGrabShootOwnPart() = default;

bool StalEnemyGrabShootOwnPart::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyGrabShootOwnPart::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalEnemyGrabShootOwnPart::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalEnemyGrabShootOwnPart::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
