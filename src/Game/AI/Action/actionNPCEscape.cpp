#include "Game/AI/Action/actionNPCEscape.h"

namespace uking::action {

NPCEscape::NPCEscape(const InitArg& arg) : RandomMoveAction(arg) {}

NPCEscape::~NPCEscape() = default;

bool NPCEscape::init_(sead::Heap* heap) {
    return RandomMoveAction::init_(heap);
}

void NPCEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    RandomMoveAction::enter_(params);
}

void NPCEscape::leave_() {
    RandomMoveAction::leave_();
}

void NPCEscape::loadParams_() {
    RandomMoveAction::loadParams_();
    getStaticParam(&mWallHitTime_s, "WallHitTime");
    getStaticParam(&mStopTime_s, "StopTime");
    getStaticParam(&mMaxDistance_s, "MaxDistance");
    getStaticParam(&mMinDistance_s, "MinDistance");
    getStaticParam(&mAngularRange_s, "AngularRange");
    getStaticParam(&mVerticalEscapeSpeed_s, "VerticalEscapeSpeed");
    getStaticParam(&mIsTurnToTargetPos_s, "IsTurnToTargetPos");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
}

void NPCEscape::calc_() {
    RandomMoveAction::calc_();
}

}  // namespace uking::action
