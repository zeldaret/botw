#include "Game/AI/Action/actionMarkPositionFromGameData.h"

namespace uking::action {

MarkPositionFromGameData::MarkPositionFromGameData(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

MarkPositionFromGameData::~MarkPositionFromGameData() = default;

bool MarkPositionFromGameData::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MarkPositionFromGameData::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MarkPositionFromGameData::leave_() {
    ksys::act::ai::Action::leave_();
}

void MarkPositionFromGameData::loadParams_() {
    getDynamicParam(&mPinColorIdx_d, "PinColorIdx");
    getDynamicParam(&mGameDataVec3_d, "GameDataVec3");
}

void MarkPositionFromGameData::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
