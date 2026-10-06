#include "Game/Actor/AI/aiHorseRiddenStatusSelector.h"

namespace uking::ai {

HorseRiddenStatusSelector::HorseRiddenStatusSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRiddenStatusSelector::~HorseRiddenStatusSelector() = default;

bool HorseRiddenStatusSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRiddenStatusSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseRiddenStatusSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRiddenStatusSelector::loadParams_() {}

}  // namespace uking::ai
