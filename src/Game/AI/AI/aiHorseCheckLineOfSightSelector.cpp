#include "Game/AI/AI/aiHorseCheckLineOfSightSelector.h"

namespace uking::ai {

HorseCheckLineOfSightSelector::HorseCheckLineOfSightSelector(const InitArg& arg)
    : HorseCheckLineOfSightSelectorBase(arg) {}

HorseCheckLineOfSightSelector::~HorseCheckLineOfSightSelector() = default;

bool HorseCheckLineOfSightSelector::init_(sead::Heap* heap) {
    return HorseCheckLineOfSightSelectorBase::init_(heap);
}

void HorseCheckLineOfSightSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseCheckLineOfSightSelectorBase::enter_(params);
}

void HorseCheckLineOfSightSelector::leave_() {
    HorseCheckLineOfSightSelectorBase::leave_();
}

void HorseCheckLineOfSightSelector::loadParams_() {
    HorseCheckLineOfSightSelectorBase::loadParams_();
}

}  // namespace uking::ai
