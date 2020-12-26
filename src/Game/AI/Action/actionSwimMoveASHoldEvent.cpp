#include "Game/AI/Action/actionSwimMoveASHoldEvent.h"

namespace uking::action {

SwimMoveASHoldEvent::SwimMoveASHoldEvent(const InitArg& arg) : SwimMoveBase(arg) {}

SwimMoveASHoldEvent::~SwimMoveASHoldEvent() = default;

bool SwimMoveASHoldEvent::init_(sead::Heap* heap) {
    return SwimMoveBase::init_(heap);
}

void SwimMoveASHoldEvent::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimMoveBase::enter_(params);
}

void SwimMoveASHoldEvent::leave_() {
    SwimMoveBase::leave_();
}

void SwimMoveASHoldEvent::loadParams_() {
    SwimMoveBase::loadParams_();
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

void SwimMoveASHoldEvent::calc_() {
    SwimMoveBase::calc_();
}

}  // namespace uking::action
