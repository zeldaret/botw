#include "Game/AI/Action/actionCopyMapPinPosition.h"

namespace uking::action {

CopyMapPinPosition::CopyMapPinPosition(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CopyMapPinPosition::~CopyMapPinPosition() = default;

bool CopyMapPinPosition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CopyMapPinPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CopyMapPinPosition::leave_() {
    ksys::act::ai::Action::leave_();
}

void CopyMapPinPosition::loadParams_() {
    getDynamicParam(&mPinColorIdx_d, "PinColorIdx");
    getDynamicParam(&mGameDataVec3_d, "GameDataVec3");
}

void CopyMapPinPosition::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
