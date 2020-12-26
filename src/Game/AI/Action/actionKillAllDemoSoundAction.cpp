#include "Game/AI/Action/actionKillAllDemoSoundAction.h"

namespace uking::action {

KillAllDemoSoundAction::KillAllDemoSoundAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KillAllDemoSoundAction::~KillAllDemoSoundAction() = default;

bool KillAllDemoSoundAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KillAllDemoSoundAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KillAllDemoSoundAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void KillAllDemoSoundAction::loadParams_() {}

void KillAllDemoSoundAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
