#include "Game/AI/Action/actionResetGimmick.h"

namespace uking::action {

ResetGimmick::ResetGimmick(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ResetGimmick::~ResetGimmick() = default;

bool ResetGimmick::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ResetGimmick::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ResetGimmick::leave_() {
    ksys::act::ai::Action::leave_();
}

void ResetGimmick::loadParams_() {
    getDynamicParam(&mSystemResetOption_d, "SystemResetOption");
    getDynamicParam(&mIsResetCamera_d, "IsResetCamera");
    getDynamicParam(&mAdditionalResetActor_d, "AdditionalResetActor");
}

void ResetGimmick::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
