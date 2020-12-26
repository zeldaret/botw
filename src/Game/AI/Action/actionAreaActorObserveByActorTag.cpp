#include "Game/AI/Action/actionAreaActorObserveByActorTag.h"

namespace uking::action {

AreaActorObserveByActorTag::AreaActorObserveByActorTag(const InitArg& arg)
    : AreaActorObserve(arg) {}

AreaActorObserveByActorTag::~AreaActorObserveByActorTag() = default;

bool AreaActorObserveByActorTag::init_(sead::Heap* heap) {
    return AreaActorObserve::init_(heap);
}

void AreaActorObserveByActorTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActorObserve::enter_(params);
}

void AreaActorObserveByActorTag::leave_() {
    AreaActorObserve::leave_();
}

void AreaActorObserveByActorTag::loadParams_() {
    getMapUnitParam(&mCount_m, "Count");
    getMapUnitParam(&mIsSendMessage_m, "IsSendMessage");
    getMapUnitParam(&mDefaultBasicSignal_m, "DefaultBasicSignal");
}

void AreaActorObserveByActorTag::calc_() {
    AreaActorObserve::calc_();
}

}  // namespace uking::action
