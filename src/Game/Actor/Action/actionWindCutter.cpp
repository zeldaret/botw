#include "Game/Actor/Action/actionWindCutter.h"

namespace uking::action {

WindCutter::WindCutter(const InitArg& arg) : EmitAttackBase(arg) {}

WindCutter::~WindCutter() = default;

bool WindCutter::init_(sead::Heap* heap) {
    return EmitAttackBase::init_(heap);
}

void WindCutter::enter_(ksys::act::ai::InlineParamPack* params) {
    EmitAttackBase::enter_(params);
}

void WindCutter::leave_() {
    EmitAttackBase::leave_();
}

void WindCutter::loadParams_() {
    EmitAttackBase::loadParams_();
    getStaticParam(&mLevelAtkMult_s, "LevelAtkMult");
    getStaticParam(&mLevelBaseScaleAdd_s, "LevelBaseScaleAdd");
    getStaticParam(&mLevelRangeMult_s, "LevelRangeMult");
    getStaticParam(&mLevelScaleMult_s, "LevelScaleMult");
    getStaticParam(&mIsLevelOneScaleOne_s, "IsLevelOneScaleOne");
    getMapUnitParam(&mAttackLevel_m, "AttackLevel");
    getMapUnitParam(&mAttackDirType_m, "AttackDirType");
    getAITreeVariable(&mAttackAttrEventKill_a, "AttackAttrEventKill");
}

void WindCutter::calc_() {
    EmitAttackBase::calc_();
}

}  // namespace uking::action
