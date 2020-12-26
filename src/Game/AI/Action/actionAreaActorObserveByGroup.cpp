#include "Game/AI/Action/actionAreaActorObserveByGroup.h"

namespace uking::action {

AreaActorObserveByGroup::AreaActorObserveByGroup(const InitArg& arg) : AreaActorObserve(arg) {}

AreaActorObserveByGroup::~AreaActorObserveByGroup() = default;

bool AreaActorObserveByGroup::init_(sead::Heap* heap) {
    return AreaActorObserve::init_(heap);
}

void AreaActorObserveByGroup::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActorObserve::enter_(params);
}

void AreaActorObserveByGroup::leave_() {
    AreaActorObserve::leave_();
}

void AreaActorObserveByGroup::loadParams_() {
    getMapUnitParam(&mCount_m, "Count");
    getMapUnitParam(&mIsSendMessage_m, "IsSendMessage");
    getMapUnitParam(&mDefaultBasicSignal_m, "DefaultBasicSignal");
}

void AreaActorObserveByGroup::calc_() {
    AreaActorObserve::calc_();
}

}  // namespace uking::action
