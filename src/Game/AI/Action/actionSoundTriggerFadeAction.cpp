#include "Game/AI/Action/actionSoundTriggerFadeAction.h"

namespace uking::action {

SoundTriggerFadeAction::SoundTriggerFadeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SoundTriggerFadeAction::~SoundTriggerFadeAction() = default;

bool SoundTriggerFadeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SoundTriggerFadeAction::loadParams_() {
    getDynamicParam(&mSound_d, "Sound");
}

}  // namespace uking::action
