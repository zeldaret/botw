#include "Game/AI/Action/actionFreeMoveRandom.h"

namespace uking::action {

FreeMoveRandom::FreeMoveRandom(const InitArg& arg) : FreeMove(arg) {}

FreeMoveRandom::~FreeMoveRandom() = default;

bool FreeMoveRandom::init_(sead::Heap* heap) {
    return FreeMove::init_(heap);
}

void FreeMoveRandom::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMove::enter_(params);
}

void FreeMoveRandom::leave_() {
    FreeMove::leave_();
}

void FreeMoveRandom::loadParams_() {
    FreeMove::loadParams_();
    getStaticParam(&mRandVertical_s, "RandVertical");
    getStaticParam(&mRandHorizontal_s, "RandHorizontal");
    getStaticParam(&mRandSpeedMax_s, "RandSpeedMax");
    getStaticParam(&mRandSpeedMin_s, "RandSpeedMin");
    getStaticParam(&mTargetDistance_s, "TargetDistance");
    getStaticParam(&mHeightMax_s, "HeightMax");
    getStaticParam(&mHeightMin_s, "HeightMin");
    getStaticParam(&mMoveAreaRadius_s, "MoveAreaRadius");
}

void FreeMoveRandom::calc_() {
    FreeMove::calc_();
}

}  // namespace uking::action
