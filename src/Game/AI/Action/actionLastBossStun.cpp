#include "Game/AI/Action/actionLastBossStun.h"

namespace uking::action {

LastBossStun::LastBossStun(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossStun::~LastBossStun() = default;

bool LastBossStun::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossStun::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossStun::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossStun::loadParams_() {
    getStaticParam(&mStunTime_s, "StunTime");
    getStaticParam(&mAddStunTime_s, "AddStunTime");
    getStaticParam(&mShockWaveDownTime_s, "ShockWaveDownTime");
}

void LastBossStun::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
