#include "Game/AI/Action/actionForceGetUpWaterFloatFreeze.h"

namespace uking::action {

ForceGetUpWaterFloatFreeze::ForceGetUpWaterFloatFreeze(const InitArg& arg)
    : WaterFloatFreeze(arg) {}

ForceGetUpWaterFloatFreeze::~ForceGetUpWaterFloatFreeze() = default;

bool ForceGetUpWaterFloatFreeze::init_(sead::Heap* heap) {
    return WaterFloatFreeze::init_(heap);
}

void ForceGetUpWaterFloatFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatFreeze::enter_(params);
}

void ForceGetUpWaterFloatFreeze::leave_() {
    WaterFloatFreeze::leave_();
}

void ForceGetUpWaterFloatFreeze::loadParams_() {
    WaterFloatFreeze::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void ForceGetUpWaterFloatFreeze::calc_() {
    WaterFloatFreeze::calc_();
}

}  // namespace uking::action
