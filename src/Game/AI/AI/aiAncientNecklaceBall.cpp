#include "Game/AI/AI/aiAncientNecklaceBall.h"

namespace uking::ai {

AncientNecklaceBall::AncientNecklaceBall(const InitArg& arg) : AncientNecklaceBallBase(arg) {}

AncientNecklaceBall::~AncientNecklaceBall() = default;

bool AncientNecklaceBall::init_(sead::Heap* heap) {
    return AncientNecklaceBallBase::init_(heap);
}

void AncientNecklaceBall::enter_(ksys::act::ai::InlineParamPack* params) {
    AncientNecklaceBallBase::enter_(params);
}

void AncientNecklaceBall::leave_() {
    AncientNecklaceBallBase::leave_();
}

void AncientNecklaceBall::loadParams_() {
    AncientNecklaceBallBase::loadParams_();
    getStaticParam(&mLandNoiseLevel_s, "LandNoiseLevel");
    getMapUnitParam(&mGrabNodeIndex_m, "GrabNodeIndex");
    getMapUnitParam(&mGiantNecklaceActiveSaveFlag_m, "GiantNecklaceActiveSaveFlag");
}

}  // namespace uking::ai
