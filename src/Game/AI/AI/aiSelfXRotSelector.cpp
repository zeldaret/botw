#include "Game/AI/AI/aiSelfXRotSelector.h"

namespace uking::ai {

SelfXRotSelector::SelfXRotSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SelfXRotSelector::~SelfXRotSelector() = default;

bool SelfXRotSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SelfXRotSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SelfXRotSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SelfXRotSelector::loadParams_() {
    getStaticParam(&mAngle_s, "Angle");
}

}  // namespace uking::ai
