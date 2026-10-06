#include "Game/Actor/AI/aiYunBoCannon.h"

namespace uking::ai {

YunBoCannon::YunBoCannon(const InitArg& arg) : BigCannon(arg) {}

YunBoCannon::~YunBoCannon() = default;

bool YunBoCannon::init_(sead::Heap* heap) {
    return BigCannon::init_(heap);
}

void YunBoCannon::enter_(ksys::act::ai::InlineParamPack* params) {
    BigCannon::enter_(params);
}

void YunBoCannon::leave_() {
    BigCannon::leave_();
}

void YunBoCannon::loadParams_() {
    BigCannon::loadParams_();
    getStaticParam(&mReturnAnchorName_s, "ReturnAnchorName");
    getMapUnitParam(&mCannonSpot_m, "CannonSpot");
    getMapUnitParam(&mActorName_m, "ActorName");
}

}  // namespace uking::ai
