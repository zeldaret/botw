#include "Game/AI/Action/actionGuardianMiniBeamMove.h"

namespace uking::action {

GuardianMiniBeamMove::GuardianMiniBeamMove(const InitArg& arg) : BeamMove(arg) {}

GuardianMiniBeamMove::~GuardianMiniBeamMove() = default;

bool GuardianMiniBeamMove::init_(sead::Heap* heap) {
    return BeamMove::init_(heap);
}

void GuardianMiniBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamMove::enter_(params);
}

void GuardianMiniBeamMove::leave_() {
    BeamMove::leave_();
}

void GuardianMiniBeamMove::loadParams_() {
    BeamMove::loadParams_();
    getStaticParam(&mReboundDeccel_s, "ReboundDeccel");
}

void GuardianMiniBeamMove::calc_() {
    BeamMove::calc_();
}

}  // namespace uking::action
