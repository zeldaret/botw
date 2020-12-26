#include "Game/AI/Action/actionListenerFixPositionAction.h"

namespace uking::action {

ListenerFixPositionAction::ListenerFixPositionAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ListenerFixPositionAction::~ListenerFixPositionAction() = default;

bool ListenerFixPositionAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ListenerFixPositionAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ListenerFixPositionAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void ListenerFixPositionAction::loadParams_() {
    getDynamicParam(&mFixType_d, "FixType");
}

void ListenerFixPositionAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
