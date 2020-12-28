#include "Game/AI/Action/actionEnvSetLensFlare.h"

namespace uking::action {

EnvSetLensFlare::EnvSetLensFlare(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool EnvSetLensFlare::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EnvSetLensFlare::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EnvSetLensFlare::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnvSetLensFlare::loadParams_() {
    getDynamicParam(&mPresetIndex_d, "PresetIndex");
}

void EnvSetLensFlare::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
