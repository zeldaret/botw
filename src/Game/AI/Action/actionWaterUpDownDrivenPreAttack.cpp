#include "Game/AI/Action/actionWaterUpDownDrivenPreAttack.h"

namespace uking::action {

WaterUpDownDrivenPreAttack::WaterUpDownDrivenPreAttack(const InitArg& arg)
    : WaterUpDownAnmDrivenMove(arg) {}

WaterUpDownDrivenPreAttack::~WaterUpDownDrivenPreAttack() = default;

bool WaterUpDownDrivenPreAttack::init_(sead::Heap* heap) {
    return WaterUpDownAnmDrivenMove::init_(heap);
}

void WaterUpDownDrivenPreAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterUpDownAnmDrivenMove::enter_(params);
}

void WaterUpDownDrivenPreAttack::leave_() {
    WaterUpDownAnmDrivenMove::leave_();
}

void WaterUpDownDrivenPreAttack::loadParams_() {
    WaterUpDownAnmDrivenMove::loadParams_();
    getStaticParam(&mTurnSpeed_s, "TurnSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void WaterUpDownDrivenPreAttack::calc_() {
    WaterUpDownAnmDrivenMove::calc_();
}

}  // namespace uking::action
