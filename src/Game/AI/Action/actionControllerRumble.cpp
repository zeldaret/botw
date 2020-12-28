#include "Game/AI/Action/actionControllerRumble.h"

namespace uking::action {

ControllerRumble::ControllerRumble(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void ControllerRumble::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ControllerRumble::loadParams_() {
    getStaticParam(&mPattern_s, "Pattern");
    getDynamicParam2(&mCount_d, "Count");
}

}  // namespace uking::action
