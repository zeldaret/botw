#include "Game/AI/AI/aiYunBoCannon.h"

namespace uking::ai {

YunBoCannon::YunBoCannon(const InitArg& arg) : GoronCannonBase(arg) {}

YunBoCannon::~YunBoCannon() = default;

bool YunBoCannon::init_(sead::Heap* heap) {
    return GoronCannonBase::init_(heap);
}

void YunBoCannon::enter_(ksys::act::ai::InlineParamPack* params) {
    GoronCannonBase::enter_(params);
}

void YunBoCannon::leave_() {
    GoronCannonBase::leave_();
}

void YunBoCannon::loadParams_() {
    GoronCannonBase::loadParams_();
    getStaticParam(&mReturnAnchorName_s, "ReturnAnchorName");
    getMapUnitParam(&mCannonSpot_m, "CannonSpot");
    getMapUnitParam(&mActorName_m, "ActorName");
}

}  // namespace uking::ai
