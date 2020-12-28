#include "Game/AI/Action/actionSwimMoveASHoldEvent.h"

namespace uking::action {

SwimMoveASHoldEvent::SwimMoveASHoldEvent(const InitArg& arg) : SwimMoveBase(arg) {}

SwimMoveASHoldEvent::~SwimMoveASHoldEvent() = default;

void SwimMoveASHoldEvent::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimMoveBase::enter_(params);
}

void SwimMoveASHoldEvent::loadParams_() {
    SwimMoveBase::loadParams_();
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
