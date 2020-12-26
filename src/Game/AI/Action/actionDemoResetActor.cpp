#include "Game/AI/Action/actionDemoResetActor.h"

namespace uking::action {

DemoResetActor::DemoResetActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoResetActor::~DemoResetActor() = default;

bool DemoResetActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoResetActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoResetActor::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoResetActor::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
}

void DemoResetActor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
