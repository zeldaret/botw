#include "Game/AI/AI/aiSwarmBattle.h"

namespace uking::ai {

SwarmBattle::SwarmBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwarmBattle::~SwarmBattle() = default;

bool SwarmBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwarmBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwarmBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwarmBattle::loadParams_() {
    getStaticParam(&mFailedRiseHeight_s, "FailedRiseHeight");
    getStaticParam(&mRiseFailedMoveDist_s, "RiseFailedMoveDist");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
}

}  // namespace uking::ai
