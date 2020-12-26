#include "Game/AI/Action/actionSetGetFlagBase.h"

namespace uking::action {

SetGetFlagBase::SetGetFlagBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetGetFlagBase::~SetGetFlagBase() = default;

bool SetGetFlagBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetGetFlagBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetGetFlagBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetGetFlagBase::loadParams_() {}

void SetGetFlagBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
