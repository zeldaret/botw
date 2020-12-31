#include "Game/AI/AI/aiAddSwarmMove.h"

namespace uking::ai {

AddSwarmMove::AddSwarmMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AddSwarmMove::~AddSwarmMove() = default;

bool AddSwarmMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddSwarmMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AddSwarmMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AddSwarmMove::loadParams_() {
    getStaticParam(&mIgnoreSensorTime_s, "IgnoreSensorTime");
    getStaticParam(&mSubSpeed_s, "SubSpeed");
    getStaticParam(&mSubAccRateMin_s, "SubAccRateMin");
    getStaticParam(&mSubAccRateMax_s, "SubAccRateMax");
    getStaticParam(&mIsEndBySensor_s, "IsEndBySensor");
    getStaticParam(&mAnimName_s, "AnimName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
