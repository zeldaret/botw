#include "Game/AI/Action/actionFreeMove.h"

namespace uking::action {

FreeMove::FreeMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FreeMove::~FreeMove() = default;

bool FreeMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FreeMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FreeMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void FreeMove::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mSpeedAddRate_s, "SpeedAddRate");
    getStaticParam(&mAngleSpeed_s, "AngleSpeed");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mAllowPitchRotation_s, "AllowPitchRotation");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void FreeMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
