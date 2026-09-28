#include "Game/Actor/AI/aiSiteBossFlameBall.h"

namespace uking::ai {

SiteBossFlameBall::SiteBossFlameBall(const InitArg& arg) : GanonFlameBall(arg) {}

SiteBossFlameBall::~SiteBossFlameBall() = default;

bool SiteBossFlameBall::init_(sead::Heap* heap) {
    return GanonFlameBall::init_(heap);
}

void SiteBossFlameBall::enter_(ksys::act::ai::InlineParamPack* params) {
    GanonFlameBall::enter_(params);
}

void SiteBossFlameBall::leave_() {
    GanonFlameBall::leave_();
}

void SiteBossFlameBall::loadParams_() {
    GanonFlameBall::loadParams_();
    getStaticParam(&mChemicalIndex_s, "ChemicalIndex");
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mMoveOffset_s, "MoveOffset");
    getStaticParam(&mCountOffset_s, "CountOffset");
    getStaticParam(&mIsInfluence_s, "IsInfluence");
    getMapUnitParam(&mCount_m, "Count");
    getMapUnitParam(&mPosOffset_m, "PosOffset");
}

}  // namespace uking::ai
