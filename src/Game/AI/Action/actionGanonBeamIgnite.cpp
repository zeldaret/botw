#include "Game/AI/Action/actionGanonBeamIgnite.h"

namespace uking::action {

GanonBeamIgnite::GanonBeamIgnite(const InitArg& arg) : OnetimeStopASPlay(arg) {}

GanonBeamIgnite::~GanonBeamIgnite() = default;

bool GanonBeamIgnite::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void GanonBeamIgnite::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void GanonBeamIgnite::leave_() {
    OnetimeStopASPlay::leave_();
}

void GanonBeamIgnite::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getStaticParam(&mIsConnectChild_s, "IsConnectChild");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getStaticParam(&mDirMinAngle_s, "DirMinAngle");
    getStaticParam(&mDirMaxAngle_s, "DirMaxAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteActor_d, "IgniteActor");
}

void GanonBeamIgnite::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
