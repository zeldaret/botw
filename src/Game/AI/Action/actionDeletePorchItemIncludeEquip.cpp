#include "Game/AI/Action/actionDeletePorchItemIncludeEquip.h"

namespace uking::action {

DeletePorchItemIncludeEquip::DeletePorchItemIncludeEquip(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DeletePorchItemIncludeEquip::~DeletePorchItemIncludeEquip() = default;

bool DeletePorchItemIncludeEquip::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DeletePorchItemIncludeEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DeletePorchItemIncludeEquip::leave_() {
    ksys::act::ai::Action::leave_();
}

void DeletePorchItemIncludeEquip::loadParams_() {
    getDynamicParam(&mDeleteNum_d, "DeleteNum");
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
}

void DeletePorchItemIncludeEquip::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
