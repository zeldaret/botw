#include "Game/AI/Action/actionGanonBoneControl.h"

namespace uking::action {

GanonBoneControl::GanonBoneControl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonBoneControl::~GanonBoneControl() = default;

bool GanonBoneControl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonBoneControl::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonBoneControl::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonBoneControl::loadParams_() {
    getDynamicParam(&mIsBattleModeOn_d, "IsBattleModeOn");
}

void GanonBoneControl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
