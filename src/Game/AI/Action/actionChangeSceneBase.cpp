#include "Game/AI/Action/actionChangeSceneBase.h"

namespace uking::action {

ChangeSceneBase::ChangeSceneBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeSceneBase::~ChangeSceneBase() = default;

bool ChangeSceneBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeSceneBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChangeSceneBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangeSceneBase::loadParams_() {
    getDynamicParam(&mStartType_d, "StartType");
    getDynamicParam(&mEvflName_d, "EvflName");
    getDynamicParam(&mEntryPointName_d, "EntryPointName");
}

void ChangeSceneBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
