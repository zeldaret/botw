#include "Game/AI/Action/actionDefRandomMoveAction.h"

namespace uking::action {

DefRandomMoveAction::DefRandomMoveAction(const InitArg& arg) : RandomMoveAction(arg) {}

void DefRandomMoveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    RandomMoveAction::enter_(params);
}

void DefRandomMoveAction::leave_() {
    RandomMoveAction::leave_();
}

void DefRandomMoveAction::loadParams_() {
    RandomMoveAction::loadParams_();
    getStaticParam(&mRadiusLimit_s, "RadiusLimit");
    getStaticParam(&mMaxMoveSpeed_s, "MaxMoveSpeed");
    getStaticParam(&mMinMoveSpeed_s, "MinMoveSpeed");
    getStaticParam(&mMaxMoveDistance_s, "MaxMoveDistance");
    getStaticParam(&mMinMoveDistance_s, "MinMoveDistance");
    getStaticParam(&mMaxMoveAngle_s, "MaxMoveAngle");
    getStaticParam(&mIsUseBasepos_s, "IsUseBasepos");
    getDynamicParam(&mBasePos_d, "BasePos");
}

void DefRandomMoveAction::calc_() {
    RandomMoveAction::calc_();
}

}  // namespace uking::action
