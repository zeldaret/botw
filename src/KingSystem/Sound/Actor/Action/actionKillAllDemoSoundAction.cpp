#include "KingSystem/Sound/Actor/Action/actionKillAllDemoSoundAction.h"

namespace ksys::snd {

KillAllDemoSoundAction::KillAllDemoSoundAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KillAllDemoSoundAction::~KillAllDemoSoundAction() = default;

bool KillAllDemoSoundAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KillAllDemoSoundAction::loadParams_() {}

}  // namespace ksys::snd
