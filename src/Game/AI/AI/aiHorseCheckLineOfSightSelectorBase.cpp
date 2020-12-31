#include "Game/AI/AI/aiHorseCheckLineOfSightSelectorBase.h"

namespace uking::ai {

HorseCheckLineOfSightSelectorBase::HorseCheckLineOfSightSelectorBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

HorseCheckLineOfSightSelectorBase::~HorseCheckLineOfSightSelectorBase() = default;

bool HorseCheckLineOfSightSelectorBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseCheckLineOfSightSelectorBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseCheckLineOfSightSelectorBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseCheckLineOfSightSelectorBase::loadParams_() {
    getStaticParam(&mDirectionNum_s, "DirectionNum");
    getStaticParam(&mDirectionAngle_s, "DirectionAngle");
    getStaticParam(&mDistance_s, "Distance");
    getStaticParam(&mRadiusScale_s, "RadiusScale");
}

}  // namespace uking::ai
