#include "Game/AI/Action/actionViewLevelFlyMove.h"

namespace uking::action {

ViewLevelFlyMove::ViewLevelFlyMove(const InitArg& arg) : WizzrobeVisibleWalk(arg) {}

ViewLevelFlyMove::~ViewLevelFlyMove() = default;

bool ViewLevelFlyMove::init_(sead::Heap* heap) {
    return WizzrobeVisibleWalk::init_(heap);
}

void ViewLevelFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    WizzrobeVisibleWalk::enter_(params);
}

void ViewLevelFlyMove::leave_() {
    WizzrobeVisibleWalk::leave_();
}

void ViewLevelFlyMove::loadParams_() {
    WizzrobeVisibleWalk::loadParams_();
    getDynamicParam(&mAttPos_d, "AttPos");
}

void ViewLevelFlyMove::calc_() {
    WizzrobeVisibleWalk::calc_();
}

}  // namespace uking::action
