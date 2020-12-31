#include "Game/AI/AI/aiTargetAttackAttitudeTgtSelectBase.h"

namespace uking::ai {

TargetAttackAttitudeTgtSelectBase::TargetAttackAttitudeTgtSelectBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

TargetAttackAttitudeTgtSelectBase::~TargetAttackAttitudeTgtSelectBase() = default;

void TargetAttackAttitudeTgtSelectBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetAttackAttitudeTgtSelectBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetAttackAttitudeTgtSelectBase::loadParams_() {}

}  // namespace uking::ai
