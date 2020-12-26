#include "Game/AI/Action/actionLastBossRailWarpAction.h"

namespace uking::action {

LastBossRailWarpAction::LastBossRailWarpAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossRailWarpAction::~LastBossRailWarpAction() = default;

bool LastBossRailWarpAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossRailWarpAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossRailWarpAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossRailWarpAction::loadParams_() {
    getStaticParam(&mWarpTime_s, "WarpTime");
    getStaticParam(&mYOffset_s, "YOffset");
    getStaticParam(&mIsUpdateHomePos_s, "IsUpdateHomePos");
    getStaticParam(&mIsTurnToPlayer_s, "IsTurnToPlayer");
    getDynamicParam(&mRailIndex_d, "RailIndex");
    getDynamicParam(&mIsPartsActorTgOn_d, "IsPartsActorTgOn");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LastBossRailWarpAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
