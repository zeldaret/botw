#include "Game/AI/Action/actionDamageTurnByWeakPoint.h"

namespace uking::action {

DamageTurnByWeakPoint::DamageTurnByWeakPoint(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DamageTurnByWeakPoint::~DamageTurnByWeakPoint() = default;

bool DamageTurnByWeakPoint::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DamageTurnByWeakPoint::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DamageTurnByWeakPoint::leave_() {
    ksys::act::ai::Action::leave_();
}

void DamageTurnByWeakPoint::loadParams_() {
    getStaticParam(&mTurnSpeed_s, "TurnSpeed");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

void DamageTurnByWeakPoint::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
