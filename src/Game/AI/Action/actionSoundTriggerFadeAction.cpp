#include "Game/AI/Action/actionSoundTriggerFadeAction.h"

namespace uking::action {

SoundTriggerFadeAction::SoundTriggerFadeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SoundTriggerFadeAction::~SoundTriggerFadeAction() = default;

bool SoundTriggerFadeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SoundTriggerFadeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SoundTriggerFadeAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SoundTriggerFadeAction::loadParams_() {
    getDynamicParam(&mSound_d, "Sound");
}

void SoundTriggerFadeAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
