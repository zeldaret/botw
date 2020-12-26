#include "Game/AI/Action/actionVacuumedItemShootToTarget.h"

namespace uking::action {

VacuumedItemShootToTarget::VacuumedItemShootToTarget(const InitArg& arg) : OnetimeStopASPlay(arg) {}

VacuumedItemShootToTarget::~VacuumedItemShootToTarget() = default;

bool VacuumedItemShootToTarget::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void VacuumedItemShootToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void VacuumedItemShootToTarget::leave_() {
    OnetimeStopASPlay::leave_();
}

void VacuumedItemShootToTarget::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    // FIXME: CALL sub_710073ED20 @ 0x710073ed20
    getStaticParam(&mIsReuseBullet_s, "IsReuseBullet");
}

void VacuumedItemShootToTarget::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
