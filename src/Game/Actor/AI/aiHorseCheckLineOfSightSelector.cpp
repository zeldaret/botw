#include "Game/Actor/AI/aiHorseCheckLineOfSightSelector.h"

namespace uking::ai {

HorseCheckLineOfSightSelector::HorseCheckLineOfSightSelector(const InitArg& arg)
    : CheckLineOfSightSelector(arg) {}

HorseCheckLineOfSightSelector::~HorseCheckLineOfSightSelector() = default;

bool HorseCheckLineOfSightSelector::init_(sead::Heap* heap) {
    return CheckLineOfSightSelector::init_(heap);
}

void HorseCheckLineOfSightSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    CheckLineOfSightSelector::enter_(params);
}

void HorseCheckLineOfSightSelector::leave_() {
    CheckLineOfSightSelector::leave_();
}

void HorseCheckLineOfSightSelector::loadParams_() {
    CheckLineOfSightSelector::loadParams_();
}

}  // namespace uking::ai
