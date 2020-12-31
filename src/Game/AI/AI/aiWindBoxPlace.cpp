#include "Game/AI/AI/aiWindBoxPlace.h"

namespace uking::ai {

WindBoxPlace::WindBoxPlace(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WindBoxPlace::~WindBoxPlace() = default;

bool WindBoxPlace::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WindBoxPlace::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WindBoxPlace::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WindBoxPlace::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getMapUnitParam(&mDirection_m, "Direction");
    getMapUnitParam(&mWindSpeed_m, "WindSpeed");
}

}  // namespace uking::ai
