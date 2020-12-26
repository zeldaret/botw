#include "Game/AI/Action/actionDgnObjDlcGondolaCreateTag.h"

namespace uking::action {

DgnObjDlcGondolaCreateTag::DgnObjDlcGondolaCreateTag(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DgnObjDlcGondolaCreateTag::~DgnObjDlcGondolaCreateTag() = default;

bool DgnObjDlcGondolaCreateTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DgnObjDlcGondolaCreateTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DgnObjDlcGondolaCreateTag::leave_() {
    ksys::act::ai::Action::leave_();
}

void DgnObjDlcGondolaCreateTag::loadParams_() {
    getStaticParam(&mActorName_s, "ActorName");
    getMapUnitParam(&mIntervalTime_m, "IntervalTime");
    getMapUnitParam(&mRailMoveSpeed_m, "RailMoveSpeed");
}

void DgnObjDlcGondolaCreateTag::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
