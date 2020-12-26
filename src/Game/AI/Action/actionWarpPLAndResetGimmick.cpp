#include "Game/AI/Action/actionWarpPLAndResetGimmick.h"

namespace uking::action {

WarpPLAndResetGimmick::WarpPLAndResetGimmick(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpPLAndResetGimmick::~WarpPLAndResetGimmick() = default;

bool WarpPLAndResetGimmick::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpPLAndResetGimmick::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpPLAndResetGimmick::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpPLAndResetGimmick::loadParams_() {
    getDynamicParam(&mSystemResetOption_d, "SystemResetOption");
    getDynamicParam(&mStartPosName_d, "StartPosName");
    getDynamicParam(&mAdditionalResetActor_d, "AdditionalResetActor");
}

void WarpPLAndResetGimmick::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
