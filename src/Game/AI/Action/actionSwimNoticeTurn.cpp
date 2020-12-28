#include "Game/AI/Action/actionSwimNoticeTurn.h"

namespace uking::action {

SwimNoticeTurn::SwimNoticeTurn(const InitArg& arg) : WaterFloatBase(arg) {}

SwimNoticeTurn::~SwimNoticeTurn() = default;

void SwimNoticeTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
}

void SwimNoticeTurn::leave_() {
    WaterFloatBase::leave_();
}

void SwimNoticeTurn::loadParams_() {
    WaterFloatBase::loadParams_();
    getStaticParam(&mAngSpd_s, "AngSpd");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SwimNoticeTurn::calc_() {
    WaterFloatBase::calc_();
}

}  // namespace uking::action
