#include "Game/AI/Action/actionDefEscapeFreeMoveAction.h"

namespace uking::action {

DefEscapeFreeMoveAction::DefEscapeFreeMoveAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DefEscapeFreeMoveAction::~DefEscapeFreeMoveAction() = default;

bool DefEscapeFreeMoveAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DefEscapeFreeMoveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DefEscapeFreeMoveAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void DefEscapeFreeMoveAction::loadParams_() {
    getStaticParam(&mRunAwaySpeed_s, "RunAwaySpeed");
    getStaticParam(&mRunAwayAngleSpeed_s, "RunAwayAngleSpeed");
    getStaticParam(&mRunAwayDistanceMax_s, "RunAwayDistanceMax");
    getStaticParam(&mRunAwayDistanceMin_s, "RunAwayDistanceMin");
    getStaticParam(&mRunAwayHeightOffset_s, "RunAwayHeightOffset");
    getStaticParam(&mAllowRandAngleVertical_s, "AllowRandAngleVertical");
    getStaticParam(&mAllowRandAngleHorizontal_s, "AllowRandAngleHorizontal");
    getStaticParam(&mInWater_s, "InWater");
    getStaticParam(&mIsSnake_s, "IsSnake");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void DefEscapeFreeMoveAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
