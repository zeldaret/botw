#include "Game/AI/Action/actionSetGetFlag.h"

namespace uking::action {

SetGetFlag::SetGetFlag(const InitArg& arg) : SetGetFlagBase(arg) {}

SetGetFlag::~SetGetFlag() = default;

bool SetGetFlag::init_(sead::Heap* heap) {
    return SetGetFlagBase::init_(heap);
}

void SetGetFlag::enter_(ksys::act::ai::InlineParamPack* params) {
    SetGetFlagBase::enter_(params);
}

void SetGetFlag::leave_() {
    SetGetFlagBase::leave_();
}

void SetGetFlag::loadParams_() {
    SetGetFlagBase::loadParams_();
}

void SetGetFlag::calc_() {
    SetGetFlagBase::calc_();
}

}  // namespace uking::action
