#include "Game/AI/AI/aiHorseNotRidden.h"

namespace uking::ai {

HorseNotRidden::HorseNotRidden(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseNotRidden::~HorseNotRidden() = default;

bool HorseNotRidden::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseNotRidden::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseNotRidden::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseNotRidden::loadParams_() {
    getStaticParam(&mEscapeCountThreshold_s, "EscapeCountThreshold");
    getStaticParam(&mNearHorseAssociationDistance_s, "NearHorseAssociationDistance");
    getStaticParam(&mEscapeDelayFramesMin_s, "EscapeDelayFramesMin");
    getStaticParam(&mEscapeDelayFramesMax_s, "EscapeDelayFramesMax");
    getStaticParam(&mCallDelayFrames_s, "CallDelayFrames");
    getStaticParam(&mAttackFrontDistance_s, "AttackFrontDistance");
    getStaticParam(&mAttackFrontAngleCos_s, "AttackFrontAngleCos");
    getStaticParam(&mAttackBackDistance_s, "AttackBackDistance");
    getStaticParam(&mAttackBackAngleCos_s, "AttackBackAngleCos");
    getStaticParam(&mAttackDefinitelyDistance_s, "AttackDefinitelyDistance");
    getStaticParam(&mAttackIntervalFrames_s, "AttackIntervalFrames");
    getStaticParam(&mMoveAttackCLOSDistanceByRadius_s, "MoveAttackCLOSDistanceByRadius");
    getStaticParam(&mCarriedItemCosThresholdForEat_s, "CarriedItemCosThresholdForEat");
    getStaticParam(&mStaggerVelocityThreshold_s, "StaggerVelocityThreshold");
    getStaticParam(&mCarriedItemPosRTYOffset_s, "CarriedItemPosRTYOffset");
    getStaticParam(&mCarriedItemPosRTYWidth_s, "CarriedItemPosRTYWidth");
    getDynamicParam(&mChildSelectAtFirst_d, "ChildSelectAtFirst");
}

}  // namespace uking::ai
