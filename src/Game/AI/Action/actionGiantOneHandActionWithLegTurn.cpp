#include "Game/AI/Action/actionGiantOneHandActionWithLegTurn.h"

namespace uking::action {

GiantOneHandActionWithLegTurn::GiantOneHandActionWithLegTurn(const InitArg& arg)
    : GiantAttackWithAS(arg) {}

GiantOneHandActionWithLegTurn::~GiantOneHandActionWithLegTurn() = default;

bool GiantOneHandActionWithLegTurn::init_(sead::Heap* heap) {
    return GiantAttackWithAS::init_(heap);
}

void GiantOneHandActionWithLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantAttackWithAS::enter_(params);
}

void GiantOneHandActionWithLegTurn::leave_() {
    GiantAttackWithAS::leave_();
}

void GiantOneHandActionWithLegTurn::loadParams_() {
    GiantAttackWithAS::loadParams_();
    getStaticParam(&mTraceLRAngleMax_s, "TraceLRAngleMax");
    getStaticParam(&mTraceLRAngleMin_s, "TraceLRAngleMin");
    getStaticParam(&mTraceDistFar_s, "TraceDistFar");
    getStaticParam(&mTraceDistNear_s, "TraceDistNear");
    getStaticParam(&mShoulderBoneName_s, "ShoulderBoneName");
    getStaticParam(&mRotOffsetMin_s, "RotOffsetMin");
    getStaticParam(&mRotOffsetMax_s, "RotOffsetMax");
    getStaticParam(&mBaseTargetPos_s, "BaseTargetPos");
}

void GiantOneHandActionWithLegTurn::calc_() {
    GiantAttackWithAS::calc_();
}

}  // namespace uking::action
