#include "KingSystem/Sound/Actor/Action/actionListenerSetModeAction.h"

namespace ksys::snd {

ListenerSetModeAction::ListenerSetModeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ListenerSetModeAction::~ListenerSetModeAction() = default;

bool ListenerSetModeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ListenerSetModeAction::loadParams_() {
    getDynamicParam(&mMode_d, "Mode");
}

}  // namespace ksys::snd
