#include "Game/AI/Action/actionSiteBossThrowParts.h"

namespace uking::action {

SiteBossThrowParts::SiteBossThrowParts(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossThrowParts::~SiteBossThrowParts() = default;

bool SiteBossThrowParts::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossThrowParts::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossThrowParts::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossThrowParts::loadParams_() {
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mMaxNoiseDist_s, "MaxNoiseDist");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getStaticParam(&mPredictionFrame_s, "PredictionFrame");
    getStaticParam(&mIsCalcNextPos_s, "IsCalcNextPos");
    getStaticParam(&mIsCheckPlayerAround_s, "IsCheckPlayerAround");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mPartsName_s, "PartsName");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getStaticParam(&mDirMinAngle_s, "DirMinAngle");
    getStaticParam(&mDirMaxAngle_s, "DirMaxAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteBaseProcHandle_d, "IgniteBaseProcHandle");
}

void SiteBossThrowParts::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
