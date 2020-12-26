#include "Game/AI/Action/actionSoundTrigger.h"

namespace uking::action {

SoundTrigger::SoundTrigger(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SoundTrigger::~SoundTrigger() = default;

bool SoundTrigger::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SoundTrigger::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SoundTrigger::leave_() {
    ksys::act::ai::Action::leave_();
}

void SoundTrigger::loadParams_() {}

void SoundTrigger::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
