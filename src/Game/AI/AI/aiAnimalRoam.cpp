#include "Game/AI/AI/aiAnimalRoam.h"

namespace uking::ai {

AnimalRoam::AnimalRoam(const InitArg& arg) : AnimalRoamBase(arg) {}

AnimalRoam::~AnimalRoam() = default;

bool AnimalRoam::init_(sead::Heap* heap) {
    return AnimalRoamBase::init_(heap);
}

void AnimalRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalRoamBase::enter_(params);
}

void AnimalRoam::leave_() {
    AnimalRoamBase::leave_();
}

void AnimalRoam::loadParams_() {
    AnimalRoamBase::loadParams_();
    getStaticParam(&mFinishChangeCount_s, "FinishChangeCount");
    getStaticParam(&mLimitRadius_s, "LimitRadius");
    getStaticParam(&mChangeWaitRate_s, "ChangeWaitRate");
    getStaticParam(&mFramesStuckOnTerrainAction_s, "FramesStuckOnTerrainAction");
    getStaticParam(&mIsSendGoalPos_s, "IsSendGoalPos");
    getStaticParam(&mCheckValidStartPos_s, "CheckValidStartPos");
    getStaticParam(&mCheckLOS_s, "CheckLOS");
}

}  // namespace uking::ai
