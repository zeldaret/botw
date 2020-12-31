#include "Game/AI/AI/aiWolfLinkGoToTarget.h"

namespace uking::ai {

WolfLinkGoToTarget::WolfLinkGoToTarget(const InitArg& arg) : HorseFollow(arg) {}

WolfLinkGoToTarget::~WolfLinkGoToTarget() = default;

bool WolfLinkGoToTarget::init_(sead::Heap* heap) {
    return HorseFollow::init_(heap);
}

void WolfLinkGoToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFollow::enter_(params);
}

void WolfLinkGoToTarget::leave_() {
    HorseFollow::leave_();
}

void WolfLinkGoToTarget::loadParams_() {
    HorseFollow::loadParams_();
}

}  // namespace uking::ai
