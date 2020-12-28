#include "Game/AI/Action/actionStartupTelescope.h"

namespace uking::action {

StartupTelescope::StartupTelescope(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StartupTelescope::~StartupTelescope() = default;

bool StartupTelescope::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartupTelescope::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StartupTelescope::loadParams_() {}

void StartupTelescope::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
