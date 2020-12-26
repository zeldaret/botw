#include "Game/AI/Action/actionCreateActorInAreaBasic.h"

namespace uking::action {

CreateActorInAreaBasic::CreateActorInAreaBasic(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CreateActorInAreaBasic::~CreateActorInAreaBasic() = default;

bool CreateActorInAreaBasic::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateActorInAreaBasic::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CreateActorInAreaBasic::leave_() {
    ksys::act::ai::Action::leave_();
}

void CreateActorInAreaBasic::loadParams_() {
    getStaticParam(&mCreateBasePosNum_s, "CreateBasePosNum");
    getStaticParam(&mCreateNewActorIntervalFirst_s, "CreateNewActorIntervalFirst");
    getStaticParam(&mCreateNewActorInterval_s, "CreateNewActorInterval");
    getStaticParam(&mCreateContinueTime_s, "CreateContinueTime");
    getStaticParam(&mAfterWaitTime_s, "AfterWaitTime");
    getStaticParam(&mIsAllowCreateNoSafeArea_s, "IsAllowCreateNoSafeArea");
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getStaticParam(&mBaseOffset_s, "BaseOffset");
    getStaticParam(&mCreateRandArea_s, "CreateRandArea");
    getStaticParam(&mProhibitedCreateArea_s, "ProhibitedCreateArea");
}

void CreateActorInAreaBasic::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
