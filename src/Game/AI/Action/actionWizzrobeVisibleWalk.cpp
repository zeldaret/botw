#include "Game/AI/Action/actionWizzrobeVisibleWalk.h"

namespace uking::action {

WizzrobeVisibleWalk::WizzrobeVisibleWalk(const InitArg& arg) : LevelFlyMove(arg) {}

WizzrobeVisibleWalk::~WizzrobeVisibleWalk() = default;

bool WizzrobeVisibleWalk::init_(sead::Heap* heap) {
    return LevelFlyMove::init_(heap);
}

void WizzrobeVisibleWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    LevelFlyMove::enter_(params);
}

void WizzrobeVisibleWalk::leave_() {
    LevelFlyMove::leave_();
}

void WizzrobeVisibleWalk::loadParams_() {
    LevelFlyMove::loadParams_();
    getStaticParam(&mAddTargetDist_s, "AddTargetDist");
    getStaticParam(&mFailMoveTimer_s, "FailMoveTimer");
    getStaticParam(&mIsCheckAnmSeqCancel_s, "IsCheckAnmSeqCancel");
    getStaticParam(&mIsNoBrake_s, "IsNoBrake");
}

void WizzrobeVisibleWalk::calc_() {
    LevelFlyMove::calc_();
}

}  // namespace uking::action
