#include "Game/Actor/AI/aiCheckLineOfSightSelector.h"

namespace uking::ai {

CheckLineOfSightSelector::CheckLineOfSightSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CheckLineOfSightSelector::~CheckLineOfSightSelector() = default;

bool CheckLineOfSightSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CheckLineOfSightSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CheckLineOfSightSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CheckLineOfSightSelector::loadParams_() {
    getStaticParam(&mDirectionNum_s, "DirectionNum");
    getStaticParam(&mDirectionAngle_s, "DirectionAngle");
    getStaticParam(&mDistance_s, "Distance");
    getStaticParam(&mRadiusScale_s, "RadiusScale");
}

}  // namespace uking::ai
