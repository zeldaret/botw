#include "Game/Actor/AI/aiAncientNecklaceBall.h"

namespace uking::ai {

AncientNecklaceBall::AncientNecklaceBall(const InitArg& arg) : PlayASSwitch(arg) {}

AncientNecklaceBall::~AncientNecklaceBall() = default;

bool AncientNecklaceBall::init_(sead::Heap* heap) {
    return PlayASSwitch::init_(heap);
}

void AncientNecklaceBall::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASSwitch::enter_(params);
}

void AncientNecklaceBall::leave_() {
    PlayASSwitch::leave_();
}

void AncientNecklaceBall::loadParams_() {
    PlayASSwitch::loadParams_();
    getStaticParam(&mLandNoiseLevel_s, "LandNoiseLevel");
    getMapUnitParam(&mGrabNodeIndex_m, "GrabNodeIndex");
    getMapUnitParam(&mGiantNecklaceActiveSaveFlag_m, "GiantNecklaceActiveSaveFlag");
}

}  // namespace uking::ai
