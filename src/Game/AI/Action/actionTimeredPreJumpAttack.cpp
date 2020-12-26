#include "Game/AI/Action/actionTimeredPreJumpAttack.h"

namespace uking::action {

TimeredPreJumpAttack::TimeredPreJumpAttack(const InitArg& arg) : PreJumpAttack(arg) {}

TimeredPreJumpAttack::~TimeredPreJumpAttack() = default;

bool TimeredPreJumpAttack::init_(sead::Heap* heap) {
    return PreJumpAttack::init_(heap);
}

void TimeredPreJumpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    PreJumpAttack::enter_(params);
}

void TimeredPreJumpAttack::leave_() {
    PreJumpAttack::leave_();
}

void TimeredPreJumpAttack::loadParams_() {
    PreJumpAttack::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
}

void TimeredPreJumpAttack::calc_() {
    PreJumpAttack::calc_();
}

}  // namespace uking::action
