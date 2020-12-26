#include "Game/AI/Action/actionSwarmAreaDamaged.h"

namespace uking::action {

SwarmAreaDamaged::SwarmAreaDamaged(const InitArg& arg) : SwarmDamagedBase(arg) {}

SwarmAreaDamaged::~SwarmAreaDamaged() = default;

bool SwarmAreaDamaged::init_(sead::Heap* heap) {
    return SwarmDamagedBase::init_(heap);
}

void SwarmAreaDamaged::enter_(ksys::act::ai::InlineParamPack* params) {
    SwarmDamagedBase::enter_(params);
}

void SwarmAreaDamaged::leave_() {
    SwarmDamagedBase::leave_();
}

void SwarmAreaDamaged::loadParams_() {
    SwarmDamagedBase::loadParams_();
    getStaticParam(&mDeadSubActorMax_s, "DeadSubActorMax");
}

void SwarmAreaDamaged::calc_() {
    SwarmDamagedBase::calc_();
}

}  // namespace uking::action
