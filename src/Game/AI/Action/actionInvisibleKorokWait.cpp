#include "Game/AI/Action/actionInvisibleKorokWait.h"

namespace uking::action {

InvisibleKorokWait::InvisibleKorokWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

InvisibleKorokWait::~InvisibleKorokWait() = default;

bool InvisibleKorokWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void InvisibleKorokWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void InvisibleKorokWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void InvisibleKorokWait::loadParams_() {
    getStaticParam(&mSpeedDecreRate_s, "SpeedDecreRate");
    getDynamicParam(&mDynStopTime_d, "DynStopTime");
}

void InvisibleKorokWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
