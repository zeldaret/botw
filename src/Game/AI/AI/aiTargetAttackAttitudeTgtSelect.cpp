#include "Game/AI/AI/aiTargetAttackAttitudeTgtSelect.h"

namespace uking::ai {

TargetAttackAttitudeTgtSelect::TargetAttackAttitudeTgtSelect(const InitArg& arg)
    : TargetAttackAttitudeTgtSelectBase(arg) {}

TargetAttackAttitudeTgtSelect::~TargetAttackAttitudeTgtSelect() = default;

void TargetAttackAttitudeTgtSelect::loadParams_() {
    TargetAttackAttitudeTgtSelectBase::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
