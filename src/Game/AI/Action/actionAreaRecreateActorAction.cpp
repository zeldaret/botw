#include "Game/AI/Action/actionAreaRecreateActorAction.h"

namespace uking::action {

AreaRecreateActorAction::AreaRecreateActorAction(const InitArg& arg) : AreaTagAction(arg) {}

AreaRecreateActorAction::~AreaRecreateActorAction() = default;

bool AreaRecreateActorAction::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void AreaRecreateActorAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void AreaRecreateActorAction::leave_() {
    AreaTagAction::leave_();
}

void AreaRecreateActorAction::loadParams_() {}

void AreaRecreateActorAction::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
