#include "Game/AI/AI/aiAwarenessScale.h"

namespace uking::ai {

AwarenessScale::AwarenessScale(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AwarenessScale::~AwarenessScale() = default;

bool AwarenessScale::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AwarenessScale::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AwarenessScale::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AwarenessScale::loadParams_() {
    getStaticParam(&mScale_s, "Scale");
}

}  // namespace uking::ai
