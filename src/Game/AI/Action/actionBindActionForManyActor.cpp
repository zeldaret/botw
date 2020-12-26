#include "Game/AI/Action/actionBindActionForManyActor.h"

namespace uking::action {

BindActionForManyActor::BindActionForManyActor(const InitArg& arg) : BindAction(arg) {}

BindActionForManyActor::~BindActionForManyActor() = default;

bool BindActionForManyActor::init_(sead::Heap* heap) {
    return BindAction::init_(heap);
}

void BindActionForManyActor::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
}

void BindActionForManyActor::leave_() {
    BindAction::leave_();
}

void BindActionForManyActor::loadParams_() {
    BindAction::loadParams_();
    getDynamicParam(&mIsKeepParentActor_d, "IsKeepParentActor");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

void BindActionForManyActor::calc_() {
    BindAction::calc_();
}

}  // namespace uking::action
