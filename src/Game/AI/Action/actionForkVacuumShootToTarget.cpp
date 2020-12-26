#include "Game/AI/Action/actionForkVacuumShootToTarget.h"

namespace uking::action {

ForkVacuumShootToTarget::ForkVacuumShootToTarget(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkVacuumShootToTarget::~ForkVacuumShootToTarget() = default;

bool ForkVacuumShootToTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkVacuumShootToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkVacuumShootToTarget::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkVacuumShootToTarget::loadParams_() {
    // FIXME: CALL sub_710073ED20 @ 0x710073ed20
    getStaticParam(&mIsReuseBullet_s, "IsReuseBullet");
}

void ForkVacuumShootToTarget::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
