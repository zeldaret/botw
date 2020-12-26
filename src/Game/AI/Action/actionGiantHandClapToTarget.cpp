#include "Game/AI/Action/actionGiantHandClapToTarget.h"

namespace uking::action {

GiantHandClapToTarget::GiantHandClapToTarget(const InitArg& arg) : PunchAttack(arg) {}

GiantHandClapToTarget::~GiantHandClapToTarget() = default;

bool GiantHandClapToTarget::init_(sead::Heap* heap) {
    return PunchAttack::init_(heap);
}

void GiantHandClapToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    PunchAttack::enter_(params);
}

void GiantHandClapToTarget::leave_() {
    PunchAttack::leave_();
}

void GiantHandClapToTarget::loadParams_() {
    PunchAttack::loadParams_();
    getStaticParam(&mAtkBodyScale_s, "AtkBodyScale");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GiantHandClapToTarget::calc_() {
    PunchAttack::calc_();
}

}  // namespace uking::action
