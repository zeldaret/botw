#include "Game/AI/Action/actionWarpPLToPosAndResetGimmick.h"

namespace uking::action {

WarpPLToPosAndResetGimmick::WarpPLToPosAndResetGimmick(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WarpPLToPosAndResetGimmick::~WarpPLToPosAndResetGimmick() = default;

bool WarpPLToPosAndResetGimmick::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpPLToPosAndResetGimmick::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpPLToPosAndResetGimmick::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpPLToPosAndResetGimmick::loadParams_() {
    getDynamicParam(&mRotationY_d, "RotationY");
    getDynamicParam(&mDestination_d, "Destination");
    getDynamicParam(&mSystemResetOption_d, "SystemResetOption");
    getDynamicParam(&mAdditionalResetActor_d, "AdditionalResetActor");
}

void WarpPLToPosAndResetGimmick::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
