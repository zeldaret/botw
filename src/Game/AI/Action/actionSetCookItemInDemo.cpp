#include "Game/AI/Action/actionSetCookItemInDemo.h"

namespace uking::action {

SetCookItemInDemo::SetCookItemInDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetCookItemInDemo::~SetCookItemInDemo() = default;

bool SetCookItemInDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetCookItemInDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetCookItemInDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetCookItemInDemo::loadParams_() {
    getDynamicParam(&mSetNum_d, "SetNum");
    getDynamicParam(&mPorchItemName01_d, "PorchItemName01");
    getDynamicParam(&mPorchItemName02_d, "PorchItemName02");
    getDynamicParam(&mPorchItemName03_d, "PorchItemName03");
    getDynamicParam(&mPorchItemName04_d, "PorchItemName04");
    getDynamicParam(&mPorchItemName05_d, "PorchItemName05");
}

void SetCookItemInDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
