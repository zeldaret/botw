#include "Game/AI/AI/aiStalEnemyChasePart.h"

namespace uking::ai {

StalEnemyChasePart::StalEnemyChasePart(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalEnemyChasePart::~StalEnemyChasePart() = default;

bool StalEnemyChasePart::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyChasePart::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalEnemyChasePart::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalEnemyChasePart::loadParams_() {
    getDynamicParam(&mIsCarried_d, "IsCarried");
    getDynamicParam(&mIsCarriedByPlayer_d, "IsCarriedByPlayer");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
