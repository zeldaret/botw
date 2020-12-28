#include "Game/AI/Action/actionCopyMapPinPosition.h"

namespace uking::action {

CopyMapPinPosition::CopyMapPinPosition(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CopyMapPinPosition::~CopyMapPinPosition() = default;

bool CopyMapPinPosition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CopyMapPinPosition::loadParams_() {
    getDynamicParam(&mPinColorIdx_d, "PinColorIdx");
    getDynamicParam(&mGameDataVec3_d, "GameDataVec3");
}

}  // namespace uking::action
