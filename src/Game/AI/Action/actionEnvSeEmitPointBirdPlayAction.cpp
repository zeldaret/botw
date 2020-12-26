#include "Game/AI/Action/actionEnvSeEmitPointBirdPlayAction.h"

namespace uking::action {

EnvSeEmitPointBirdPlayAction::EnvSeEmitPointBirdPlayAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EnvSeEmitPointBirdPlayAction::~EnvSeEmitPointBirdPlayAction() = default;

bool EnvSeEmitPointBirdPlayAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EnvSeEmitPointBirdPlayAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EnvSeEmitPointBirdPlayAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnvSeEmitPointBirdPlayAction::loadParams_() {}

void EnvSeEmitPointBirdPlayAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
