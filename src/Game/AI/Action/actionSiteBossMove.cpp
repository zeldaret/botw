#include "Game/AI/Action/actionSiteBossMove.h"

namespace uking::action {

SiteBossMove::SiteBossMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossMove::~SiteBossMove() = default;

bool SiteBossMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossMove::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mUpdownSpeed_s, "UpdownSpeed");
    getStaticParam(&mAmplitude_s, "Amplitude");
    getStaticParam(&mRotateRate_s, "RotateRate");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveDstPos_d, "MoveDstPos");
}

void SiteBossMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
