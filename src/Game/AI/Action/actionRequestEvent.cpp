#include "Game/AI/Action/actionRequestEvent.h"

namespace uking::action {

RequestEvent::RequestEvent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RequestEvent::~RequestEvent() = default;

bool RequestEvent::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RequestEvent::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RequestEvent::leave_() {
    ksys::act::ai::Action::leave_();
}

void RequestEvent::loadParams_() {
    getStaticParam(&mIsSelfEvent_s, "IsSelfEvent");
    getStaticParam(&mIsAddEntrySelfName_s, "IsAddEntrySelfName");
    getStaticParam(&mIsLoadEvent_s, "IsLoadEvent");
    getStaticParam(&mIsPauseOtherActors_s, "IsPauseOtherActors");
    getStaticParam(&mIsWaitRun_s, "IsWaitRun");
    getStaticParam(&mEventName_s, "EventName");
    getStaticParam(&mEntryPointName_s, "EntryPointName");
}

void RequestEvent::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
