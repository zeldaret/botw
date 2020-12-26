#include "Game/AI/Action/actionSoundProxyRootAction.h"

namespace uking::action {

SoundProxyRootAction::SoundProxyRootAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SoundProxyRootAction::~SoundProxyRootAction() = default;

bool SoundProxyRootAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SoundProxyRootAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SoundProxyRootAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SoundProxyRootAction::loadParams_() {}

void SoundProxyRootAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
