#include "Game/Actor/AI/aiTargetAttackAttitudeTgtSelect.h"

namespace uking::ai {

TargetAttackAttitudeTgtSelect::TargetAttackAttitudeTgtSelect(const InitArg& arg)
    : TargetAttackAttitudeTgt(arg) {}

TargetAttackAttitudeTgtSelect::~TargetAttackAttitudeTgtSelect() = default;

void TargetAttackAttitudeTgtSelect::loadParams_() {
    TargetAttackAttitudeTgt::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
