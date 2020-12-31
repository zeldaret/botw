#include "Game/AI/AI/aiWolfLinkFollowPlayerRoot.h"

namespace uking::ai {

WolfLinkFollowPlayerRoot::WolfLinkFollowPlayerRoot(const InitArg& arg) : HorseFollow(arg) {}

WolfLinkFollowPlayerRoot::~WolfLinkFollowPlayerRoot() = default;

bool WolfLinkFollowPlayerRoot::init_(sead::Heap* heap) {
    return HorseFollow::init_(heap);
}

void WolfLinkFollowPlayerRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFollow::enter_(params);
}

void WolfLinkFollowPlayerRoot::leave_() {
    HorseFollow::leave_();
}

void WolfLinkFollowPlayerRoot::loadParams_() {
    HorseFollow::loadParams_();
    getStaticParam(&mLateralDistance_s, "LateralDistance");
    getStaticParam(&mAnteriorDistanceStop_s, "AnteriorDistanceStop");
    getStaticParam(&mAnteriorDistanceRun_s, "AnteriorDistanceRun");
    getStaticParam(&mAnteriorDistanceSprint_s, "AnteriorDistanceSprint");
}

}  // namespace uking::ai
