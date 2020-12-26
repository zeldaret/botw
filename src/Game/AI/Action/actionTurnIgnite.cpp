#include "Game/AI/Action/actionTurnIgnite.h"

namespace uking::action {

TurnIgnite::TurnIgnite(const InitArg& arg) : StopASIgnite(arg) {}

TurnIgnite::~TurnIgnite() = default;

bool TurnIgnite::init_(sead::Heap* heap) {
    return StopASIgnite::init_(heap);
}

void TurnIgnite::enter_(ksys::act::ai::InlineParamPack* params) {
    StopASIgnite::enter_(params);
}

void TurnIgnite::leave_() {
    StopASIgnite::leave_();
}

void TurnIgnite::loadParams_() {
    StopASIgnite::loadParams_();
    getStaticParam(&mRotSpd_s, "RotSpd");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TurnIgnite::calc_() {
    StopASIgnite::calc_();
}

}  // namespace uking::action
