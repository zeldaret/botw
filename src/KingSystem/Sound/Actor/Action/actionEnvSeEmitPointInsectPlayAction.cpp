#include "KingSystem/Sound/Actor/Action/actionEnvSeEmitPointInsectPlayAction.h"

namespace ksys::snd {

EnvSeEmitPointInsectPlayAction::EnvSeEmitPointInsectPlayAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EnvSeEmitPointInsectPlayAction::~EnvSeEmitPointInsectPlayAction() = default;

bool EnvSeEmitPointInsectPlayAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EnvSeEmitPointInsectPlayAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EnvSeEmitPointInsectPlayAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnvSeEmitPointInsectPlayAction::loadParams_() {}

void EnvSeEmitPointInsectPlayAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace ksys::snd
