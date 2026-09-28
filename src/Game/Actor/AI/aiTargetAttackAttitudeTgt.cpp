#include "Game/Actor/AI/aiTargetAttackAttitudeTgt.h"

namespace uking::ai {

TargetAttackAttitudeTgt::TargetAttackAttitudeTgt(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetAttackAttitudeTgt::~TargetAttackAttitudeTgt() = default;

void TargetAttackAttitudeTgt::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetAttackAttitudeTgt::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetAttackAttitudeTgt::loadParams_() {}

}  // namespace uking::ai
