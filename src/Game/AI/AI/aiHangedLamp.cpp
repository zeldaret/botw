#include "Game/AI/AI/aiHangedLamp.h"

namespace uking::ai {

HangedLamp::HangedLamp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HangedLamp::~HangedLamp() = default;

bool HangedLamp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HangedLamp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HangedLamp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HangedLamp::loadParams_() {
    getStaticParam(&mDisableImpulseByArrow_s, "DisableImpulseByArrow");
}

}  // namespace uking::ai
