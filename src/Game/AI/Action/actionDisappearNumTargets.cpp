#include "Game/AI/Action/actionDisappearNumTargets.h"

namespace uking::action {

DisappearNumTargets::DisappearNumTargets(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DisappearNumTargets::~DisappearNumTargets() = default;

bool DisappearNumTargets::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DisappearNumTargets::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DisappearNumTargets::leave_() {
    ksys::act::ai::Action::leave_();
}

void DisappearNumTargets::loadParams_() {}

void DisappearNumTargets::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
