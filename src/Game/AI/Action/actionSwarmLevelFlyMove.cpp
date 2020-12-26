#include "Game/AI/Action/actionSwarmLevelFlyMove.h"

namespace uking::action {

SwarmLevelFlyMove::SwarmLevelFlyMove(const InitArg& arg) : LevelFlyMoveBase(arg) {}

SwarmLevelFlyMove::~SwarmLevelFlyMove() = default;

bool SwarmLevelFlyMove::init_(sead::Heap* heap) {
    return LevelFlyMoveBase::init_(heap);
}

void SwarmLevelFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    LevelFlyMoveBase::enter_(params);
}

void SwarmLevelFlyMove::leave_() {
    LevelFlyMoveBase::leave_();
}

void SwarmLevelFlyMove::loadParams_() {
    LevelFlyMoveBase::loadParams_();
    getStaticParam(&mIgnoreSensorTime_s, "IgnoreSensorTime");
    getStaticParam(&mSubAccRateMin_s, "SubAccRateMin");
    getStaticParam(&mSubAccRateMax_s, "SubAccRateMax");
    getStaticParam(&mMaterialAnimFrame_s, "MaterialAnimFrame");
    getStaticParam(&mMaterialAnimName_s, "MaterialAnimName");
}

void SwarmLevelFlyMove::calc_() {
    LevelFlyMoveBase::calc_();
}

}  // namespace uking::action
