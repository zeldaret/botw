#include "Game/Actor/Action/actionTurnGiantAttack.h"

namespace uking::action {

TurnGiantAttack::TurnGiantAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TurnGiantAttack::~TurnGiantAttack() = default;

bool TurnGiantAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TurnGiantAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TurnGiantAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void TurnGiantAttack::loadParams_() {
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mRotBaseBoneName_s, "RotBaseBoneName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TurnGiantAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
