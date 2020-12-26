#include "Game/AI/Action/actionEventBind.h"

namespace uking::action {

EventBind::EventBind(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventBind::~EventBind() = default;

bool EventBind::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventBind::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventBind::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventBind::loadParams_() {
    getDynamicParam(&mRotOffsetX_d, "RotOffsetX");
    getDynamicParam(&mRotOffsetY_d, "RotOffsetY");
    getDynamicParam(&mRotOffsetZ_d, "RotOffsetZ");
    getDynamicParam(&mTransOffsetX_d, "TransOffsetX");
    getDynamicParam(&mTransOffsetY_d, "TransOffsetY");
    getDynamicParam(&mTransOffsetZ_d, "TransOffsetZ");
    getDynamicParam(&mIsContinueBind_d, "IsContinueBind");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mNodeName_d, "NodeName");
    getAITreeVariable(&mEventBindUnit_a, "EventBindUnit");
}

void EventBind::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
