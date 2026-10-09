#include "Game/Actor/Action/actionOneHandActionWithLegTurn.h"

namespace uking::action {

OneHandActionWithLegTurn::OneHandActionWithLegTurn(const InitArg& arg) : AttackWithAS(arg) {}

OneHandActionWithLegTurn::~OneHandActionWithLegTurn() = default;

bool OneHandActionWithLegTurn::init_(sead::Heap* heap) {
    return AttackWithAS::init_(heap);
}

void OneHandActionWithLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    AttackWithAS::enter_(params);
}

void OneHandActionWithLegTurn::leave_() {
    AttackWithAS::leave_();
}

void OneHandActionWithLegTurn::loadParams_() {
    AttackWithAS::loadParams_();
    getStaticParam(&mTraceLRAngleMax_s, "TraceLRAngleMax");
    getStaticParam(&mTraceLRAngleMin_s, "TraceLRAngleMin");
    getStaticParam(&mTraceDistFar_s, "TraceDistFar");
    getStaticParam(&mTraceDistNear_s, "TraceDistNear");
    getStaticParam(&mShoulderBoneName_s, "ShoulderBoneName");
    getStaticParam(&mRotOffsetMin_s, "RotOffsetMin");
    getStaticParam(&mRotOffsetMax_s, "RotOffsetMax");
    getStaticParam(&mBaseTargetPos_s, "BaseTargetPos");
}

void OneHandActionWithLegTurn::calc_() {
    AttackWithAS::calc_();
}

}  // namespace uking::action
