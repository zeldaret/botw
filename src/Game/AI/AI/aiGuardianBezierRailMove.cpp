#include "Game/AI/AI/aiGuardianBezierRailMove.h"

namespace uking::ai {

GuardianBezierRailMove::GuardianBezierRailMove(const InitArg& arg) : RailMoveWithClose(arg) {}

GuardianBezierRailMove::~GuardianBezierRailMove() = default;

bool GuardianBezierRailMove::init_(sead::Heap* heap) {
    return RailMoveWithClose::init_(heap);
}

void GuardianBezierRailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveWithClose::enter_(params);
}

void GuardianBezierRailMove::leave_() {
    RailMoveWithClose::leave_();
}

void GuardianBezierRailMove::loadParams_() {
    RailMoveWithClose::loadParams_();
}

}  // namespace uking::ai
