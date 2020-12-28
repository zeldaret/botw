#include "Game/AI/Action/actionKillAllDemoSoundAction.h"

namespace uking::action {

KillAllDemoSoundAction::KillAllDemoSoundAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KillAllDemoSoundAction::~KillAllDemoSoundAction() = default;

bool KillAllDemoSoundAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KillAllDemoSoundAction::loadParams_() {}

}  // namespace uking::action
