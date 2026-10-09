#include "Game/Actor/Action/actionDemoApplyDamageBase.h"

namespace uking::action {

DemoApplyDamageBase::DemoApplyDamageBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoApplyDamageBase::~DemoApplyDamageBase() = default;

bool DemoApplyDamageBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoApplyDamageBase::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
}

}  // namespace uking::action
