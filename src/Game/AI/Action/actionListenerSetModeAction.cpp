#include "Game/AI/Action/actionListenerSetModeAction.h"

namespace uking::action {

ListenerSetModeAction::ListenerSetModeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ListenerSetModeAction::~ListenerSetModeAction() = default;

bool ListenerSetModeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ListenerSetModeAction::loadParams_() {
    getDynamicParam(&mMode_d, "Mode");
}

}  // namespace uking::action
