#include "Game/AI/AI/aiCreateActorWithTarget.h"

namespace uking::ai {

CreateActorWithTarget::CreateActorWithTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CreateActorWithTarget::~CreateActorWithTarget() = default;

bool CreateActorWithTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CreateActorWithTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CreateActorWithTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CreateActorWithTarget::loadParams_() {
    getStaticParam(&mCreateNewActorInterval_s, "CreateNewActorInterval");
    getStaticParam(&mCreateBasePosNum_s, "CreateBasePosNum");
    getStaticParam(&mCreateContinueTime_s, "CreateContinueTime");
    getStaticParam(&mAfterWaitTime_s, "AfterWaitTime");
    getStaticParam(&mIsAllowCreateNoSafeArea_s, "IsAllowCreateNoSafeArea");
    getStaticParam(&mIsRotateTargetDir_s, "IsRotateTargetDir");
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getStaticParam(&mBaseOffset_s, "BaseOffset");
    getStaticParam(&mCreateRandArea_s, "CreateRandArea");
    getStaticParam(&mProhibitedCreateArea_s, "ProhibitedCreateArea");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
