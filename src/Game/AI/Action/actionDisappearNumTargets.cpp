#include "Game/AI/Action/actionDisappearNumTargets.h"

namespace uking::action {

DisappearNumTargets::DisappearNumTargets(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DisappearNumTargets::~DisappearNumTargets() = default;

bool DisappearNumTargets::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DisappearNumTargets::loadParams_() {}

}  // namespace uking::action
