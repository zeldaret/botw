#include "Game/AI/Action/actionHoverBase.h"

namespace uking::action {

HoverBase::HoverBase(const InitArg& arg) : FreeMovingAction(arg) {}

bool HoverBase::init_(sead::Heap* heap) {
    return FreeMovingAction::init_(heap);
}

void HoverBase::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMovingAction::enter_(params);
}

void HoverBase::leave_() {
    FreeMovingAction::leave_();
}

void HoverBase::loadParams_() {
    FreeMovingAction::loadParams_();
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
}

void HoverBase::calc_() {
    FreeMovingAction::calc_();
}

}  // namespace uking::action
