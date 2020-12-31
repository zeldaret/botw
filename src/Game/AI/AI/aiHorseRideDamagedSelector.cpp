#include "Game/AI/AI/aiHorseRideDamagedSelector.h"

namespace uking::ai {

HorseRideDamagedSelector::HorseRideDamagedSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRideDamagedSelector::~HorseRideDamagedSelector() = default;

bool HorseRideDamagedSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideDamagedSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseRideDamagedSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideDamagedSelector::loadParams_() {}

}  // namespace uking::ai
