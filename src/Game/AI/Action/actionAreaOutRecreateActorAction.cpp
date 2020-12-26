#include "Game/AI/Action/actionAreaOutRecreateActorAction.h"

namespace uking::action {

AreaOutRecreateActorAction::AreaOutRecreateActorAction(const InitArg& arg) : AreaTagAction(arg) {}

AreaOutRecreateActorAction::~AreaOutRecreateActorAction() = default;

bool AreaOutRecreateActorAction::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void AreaOutRecreateActorAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void AreaOutRecreateActorAction::leave_() {
    AreaTagAction::leave_();
}

void AreaOutRecreateActorAction::loadParams_() {}

void AreaOutRecreateActorAction::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
