#include "Game/AI/Action/actionMarkPositionFromGameData.h"

namespace uking::action {

MarkPositionFromGameData::MarkPositionFromGameData(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

MarkPositionFromGameData::~MarkPositionFromGameData() = default;

bool MarkPositionFromGameData::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MarkPositionFromGameData::loadParams_() {
    getDynamicParam(&mPinColorIdx_d, "PinColorIdx");
    getDynamicParam(&mGameDataVec3_d, "GameDataVec3");
}

}  // namespace uking::action
