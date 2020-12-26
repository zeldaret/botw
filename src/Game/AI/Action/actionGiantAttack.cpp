#include "Game/AI/Action/actionGiantAttack.h"

namespace uking::action {

GiantAttack::GiantAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GiantAttack::~GiantAttack() = default;

bool GiantAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GiantAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GiantAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void GiantAttack::loadParams_() {
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mRotBaseBoneName_s, "RotBaseBoneName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GiantAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
