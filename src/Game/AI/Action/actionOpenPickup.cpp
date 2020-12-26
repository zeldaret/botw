#include "Game/AI/Action/actionOpenPickup.h"

namespace uking::action {

OpenPickup::OpenPickup(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenPickup::~OpenPickup() = default;

bool OpenPickup::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenPickup::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenPickup::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenPickup::loadParams_() {
    getDynamicParam(&mIsAddPorch_d, "IsAddPorch");
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
}

void OpenPickup::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
