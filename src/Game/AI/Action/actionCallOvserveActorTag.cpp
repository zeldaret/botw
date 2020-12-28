#include "Game/AI/Action/actionCallOvserveActorTag.h"

namespace uking::action {

CallOvserveActorTag::CallOvserveActorTag(const InitArg& arg) : AreaObserveActorAction(arg) {}

CallOvserveActorTag::~CallOvserveActorTag() = default;

bool CallOvserveActorTag::init_(sead::Heap* heap) {
    return AreaObserveActorAction::init_(heap);
}

void CallOvserveActorTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaObserveActorAction::enter_(params);
}

void CallOvserveActorTag::leave_() {
    AreaObserveActorAction::leave_();
}

void CallOvserveActorTag::calc_() {
    AreaObserveActorAction::calc_();
}

}  // namespace uking::action
