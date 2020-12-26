#include "Game/AI/Action/actionListenerSetModeAction.h"

namespace uking::action {

ListenerSetModeAction::ListenerSetModeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ListenerSetModeAction::~ListenerSetModeAction() = default;

bool ListenerSetModeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ListenerSetModeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ListenerSetModeAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void ListenerSetModeAction::loadParams_() {
    getDynamicParam(&mMode_d, "Mode");
}

void ListenerSetModeAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
