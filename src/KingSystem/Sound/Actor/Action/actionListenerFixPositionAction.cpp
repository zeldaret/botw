#include "KingSystem/Sound/Actor/Action/actionListenerFixPositionAction.h"

namespace ksys::snd {

ListenerFixPositionAction::ListenerFixPositionAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ListenerFixPositionAction::~ListenerFixPositionAction() = default;

bool ListenerFixPositionAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ListenerFixPositionAction::loadParams_() {
    getDynamicParam(&mFixType_d, "FixType");
}

}  // namespace ksys::snd
