#include "Game/AI/Action/actionSwarmDamaged.h"

namespace uking::action {

SwarmDamaged::SwarmDamaged(const InitArg& arg) : SwarmDamagedBase(arg) {}

SwarmDamaged::~SwarmDamaged() = default;

bool SwarmDamaged::init_(sead::Heap* heap) {
    return SwarmDamagedBase::init_(heap);
}

void SwarmDamaged::enter_(ksys::act::ai::InlineParamPack* params) {
    SwarmDamagedBase::enter_(params);
}

void SwarmDamaged::leave_() {
    SwarmDamagedBase::leave_();
}

void SwarmDamaged::loadParams_() {
    SwarmDamagedBase::loadParams_();
    getStaticParam(&mDeadSubActorMax_s, "DeadSubActorMax");
}

void SwarmDamaged::calc_() {
    SwarmDamagedBase::calc_();
}

}  // namespace uking::action
