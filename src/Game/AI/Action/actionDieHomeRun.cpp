#include "Game/AI/Action/actionDieHomeRun.h"

namespace uking::action {

DieHomeRun::DieHomeRun(const InitArg& arg) : Die(arg) {}

DieHomeRun::~DieHomeRun() = default;

bool DieHomeRun::init_(sead::Heap* heap) {
    return Die::init_(heap);
}

void DieHomeRun::enter_(ksys::act::ai::InlineParamPack* params) {
    Die::enter_(params);
}

void DieHomeRun::leave_() {
    Die::leave_();
}

void DieHomeRun::loadParams_() {
    Die::loadParams_();
    getStaticParam(&mToStarHeight_s, "ToStarHeight");
    getStaticParam(&mFallHeight_s, "FallHeight");
}

void DieHomeRun::calc_() {
    Die::calc_();
}

}  // namespace uking::action
