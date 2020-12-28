#include "Game/AI/Action/actionSetCookItemInDemo.h"

namespace uking::action {

SetCookItemInDemo::SetCookItemInDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetCookItemInDemo::~SetCookItemInDemo() = default;

bool SetCookItemInDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetCookItemInDemo::loadParams_() {
    getDynamicParam(&mSetNum_d, "SetNum");
    getDynamicParam(&mPorchItemName01_d, "PorchItemName01");
    getDynamicParam(&mPorchItemName02_d, "PorchItemName02");
    getDynamicParam(&mPorchItemName03_d, "PorchItemName03");
    getDynamicParam(&mPorchItemName04_d, "PorchItemName04");
    getDynamicParam(&mPorchItemName05_d, "PorchItemName05");
}

}  // namespace uking::action
