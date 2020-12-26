#include "Game/AI/Action/actionRequestEventFromMapUnit.h"

namespace uking::action {

RequestEventFromMapUnit::RequestEventFromMapUnit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RequestEventFromMapUnit::~RequestEventFromMapUnit() = default;

bool RequestEventFromMapUnit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RequestEventFromMapUnit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RequestEventFromMapUnit::leave_() {
    ksys::act::ai::Action::leave_();
}

void RequestEventFromMapUnit::loadParams_() {
    getStaticParam(&mIsWaitStartEvent_s, "IsWaitStartEvent");
    getStaticParam(&mASKey_s, "ASKey");
    getMapUnitParam(&mEventFlowName_m, "EventFlowName");
    getMapUnitParam(&mEventFlowEntryName_m, "EventFlowEntryName");
}

void RequestEventFromMapUnit::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
