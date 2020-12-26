#include "Game/AI/Action/actionForkAerialAcrobatics.h"

namespace uking::action {

ForkAerialAcrobatics::ForkAerialAcrobatics(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAerialAcrobatics::~ForkAerialAcrobatics() = default;

bool ForkAerialAcrobatics::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAerialAcrobatics::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAerialAcrobatics::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAerialAcrobatics::loadParams_() {
    getStaticParam(&mSpeedKeepRatio_s, "SpeedKeepRatio");
    getStaticParam(&mRotSpeedKeepRatio_s, "RotSpeedKeepRatio");
    getStaticParam(&mMinGravityScale_s, "MinGravityScale");
    getStaticParam(&mGravityPer_s, "GravityPer");
    getStaticParam(&mRetGravityPer_s, "RetGravityPer");
    getStaticParam(&mIsStopGravitySpeed_s, "IsStopGravitySpeed");
}

void ForkAerialAcrobatics::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
