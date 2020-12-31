#include "Game/AI/AI/aiHorsePrevRiddenStatusSelector.h"

namespace uking::ai {

HorsePrevRiddenStatusSelector::HorsePrevRiddenStatusSelector(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

HorsePrevRiddenStatusSelector::~HorsePrevRiddenStatusSelector() = default;

bool HorsePrevRiddenStatusSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorsePrevRiddenStatusSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorsePrevRiddenStatusSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorsePrevRiddenStatusSelector::loadParams_() {}

}  // namespace uking::ai
