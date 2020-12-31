#include "Game/AI/AI/aiRemainsElectricBGCamera.h"

namespace uking::ai {

RemainsElectricBGCamera::RemainsElectricBGCamera(const InitArg& arg)
    : RailMoveRemainsBGCamera(arg) {}

RemainsElectricBGCamera::~RemainsElectricBGCamera() = default;

bool RemainsElectricBGCamera::init_(sead::Heap* heap) {
    return RailMoveRemainsBGCamera::init_(heap);
}

void RemainsElectricBGCamera::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveRemainsBGCamera::enter_(params);
}

void RemainsElectricBGCamera::leave_() {
    RailMoveRemainsBGCamera::leave_();
}

void RemainsElectricBGCamera::loadParams_() {
    RailMoveRemainsBGCamera::loadParams_();
    getStaticParam(&mParentActorName_s, "ParentActorName");
}

}  // namespace uking::ai
