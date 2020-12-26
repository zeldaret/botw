#include "Game/AI/Action/actionSwarmGullMove.h"

namespace uking::action {

SwarmGullMove::SwarmGullMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwarmGullMove::~SwarmGullMove() = default;

bool SwarmGullMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwarmGullMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwarmGullMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void SwarmGullMove::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getMapUnitParam(&mSubUnitNum_m, "SubUnitNum");
    getMapUnitParam(&mCreateMaxRadius_m, "CreateMaxRadius");
    getMapUnitParam(&mCreateMinRadius_m, "CreateMinRadius");
    getMapUnitParam(&mCreateHeightRange_m, "CreateHeightRange");
    getMapUnitParam(&mRoundMaxRadius_m, "RoundMaxRadius");
    getMapUnitParam(&mRoundMinRadius_m, "RoundMinRadius");
    getMapUnitParam(&mCrySoundIntervalMin_m, "CrySoundIntervalMin");
    getMapUnitParam(&mCrySoundIntervalMax_m, "CrySoundIntervalMax");
}

void SwarmGullMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
