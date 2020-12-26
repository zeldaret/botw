#include "Game/AI/Action/actionOnLeaveAttackInterval.h"

namespace uking::action {

OnLeaveAttackInterval::OnLeaveAttackInterval(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OnLeaveAttackInterval::~OnLeaveAttackInterval() = default;

bool OnLeaveAttackInterval::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OnLeaveAttackInterval::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OnLeaveAttackInterval::leave_() {
    ksys::act::ai::Action::leave_();
}

void OnLeaveAttackInterval::loadParams_() {}

void OnLeaveAttackInterval::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
