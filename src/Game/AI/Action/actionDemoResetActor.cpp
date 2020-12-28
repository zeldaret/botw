#include "Game/AI/Action/actionDemoResetActor.h"

namespace uking::action {

DemoResetActor::DemoResetActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoResetActor::~DemoResetActor() = default;

bool DemoResetActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoResetActor::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
}

}  // namespace uking::action
