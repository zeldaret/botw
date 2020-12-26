#include "Game/AI/Action/actionSwarmFlyMove.h"

namespace uking::action {

SwarmFlyMove::SwarmFlyMove(const InitArg& arg) : FlyMoveBase(arg) {}

SwarmFlyMove::~SwarmFlyMove() = default;

bool SwarmFlyMove::init_(sead::Heap* heap) {
    return FlyMoveBase::init_(heap);
}

void SwarmFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyMoveBase::enter_(params);
}

void SwarmFlyMove::leave_() {
    FlyMoveBase::leave_();
}

void SwarmFlyMove::loadParams_() {
    FlyMoveBase::loadParams_();
    getStaticParam(&mIgnoreSensorTime_s, "IgnoreSensorTime");
    getStaticParam(&mSubAccRateMin_s, "SubAccRateMin");
    getStaticParam(&mSubAccRateMax_s, "SubAccRateMax");
    getStaticParam(&mMaterialAnimFrame_s, "MaterialAnimFrame");
    getStaticParam(&mMaterialAnimName_s, "MaterialAnimName");
}

void SwarmFlyMove::calc_() {
    FlyMoveBase::calc_();
}

}  // namespace uking::action
