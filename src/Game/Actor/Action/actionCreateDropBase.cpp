#include "Game/Actor/Action/actionCreateDropBase.h"

namespace uking::action {

CreateDropBase::CreateDropBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CreateDropBase::~CreateDropBase() = default;

bool CreateDropBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateDropBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CreateDropBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void CreateDropBase::loadParams_() {}

void CreateDropBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
