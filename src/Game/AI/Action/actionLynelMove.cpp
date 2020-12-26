#include "Game/AI/Action/actionLynelMove.h"

namespace uking::action {

LynelMove::LynelMove(const InitArg& arg) : AnimalMove(arg) {}

LynelMove::~LynelMove() = default;

bool LynelMove::init_(sead::Heap* heap) {
    return AnimalMove::init_(heap);
}

void LynelMove::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMove::enter_(params);
}

void LynelMove::leave_() {
    AnimalMove::leave_();
}

void LynelMove::loadParams_() {
    AnimalMove::loadParams_();
    getStaticParam(&mTimeForCalcCheckCliffDist_s, "TimeForCalcCheckCliffDist");
    // FIXME: CALL sub_710070F984 @ 0x710070f984
}

void LynelMove::calc_() {
    AnimalMove::calc_();
}

}  // namespace uking::action
