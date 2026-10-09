#include "Game/Actor/Action/actionDestPlayerWarpBase.h"

namespace uking::action {

DestPlayerWarpBase::DestPlayerWarpBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DestPlayerWarpBase::~DestPlayerWarpBase() = default;

bool DestPlayerWarpBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DestPlayerWarpBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DestPlayerWarpBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void DestPlayerWarpBase::loadParams_() {}

void DestPlayerWarpBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
