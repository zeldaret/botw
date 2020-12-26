#include "Game/AI/Action/actionAreaActorObserve.h"

namespace uking::action {

AreaActorObserve::AreaActorObserve(const InitArg& arg) : AreaTagAction(arg) {}

AreaActorObserve::~AreaActorObserve() = default;

bool AreaActorObserve::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void AreaActorObserve::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void AreaActorObserve::leave_() {
    AreaTagAction::leave_();
}

void AreaActorObserve::loadParams_() {
    getMapUnitParam(&mCount_m, "Count");
    getMapUnitParam(&mIsSendMessage_m, "IsSendMessage");
    getMapUnitParam(&mDefaultBasicSignal_m, "DefaultBasicSignal");
}

void AreaActorObserve::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
