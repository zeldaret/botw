#include "Game/AI/Action/actionSetGetFlagByActorName.h"

namespace uking::action {

SetGetFlagByActorName::SetGetFlagByActorName(const InitArg& arg) : SetGetFlagBase(arg) {}

SetGetFlagByActorName::~SetGetFlagByActorName() = default;

bool SetGetFlagByActorName::init_(sead::Heap* heap) {
    return SetGetFlagBase::init_(heap);
}

void SetGetFlagByActorName::enter_(ksys::act::ai::InlineParamPack* params) {
    SetGetFlagBase::enter_(params);
}

void SetGetFlagByActorName::leave_() {
    SetGetFlagBase::leave_();
}

void SetGetFlagByActorName::loadParams_() {
    SetGetFlagBase::loadParams_();
    getDynamicParam(&mActorName_d, "ActorName");
}

void SetGetFlagByActorName::calc_() {
    SetGetFlagBase::calc_();
}

}  // namespace uking::action
