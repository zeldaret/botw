#include "Game/AI/Action/actionGanonBeamMove.h"

namespace uking::action {

GanonBeamMove::GanonBeamMove(const InitArg& arg) : BeamMove(arg) {}

GanonBeamMove::~GanonBeamMove() = default;

bool GanonBeamMove::init_(sead::Heap* heap) {
    return BeamMove::init_(heap);
}

void GanonBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamMove::enter_(params);
}

void GanonBeamMove::leave_() {
    BeamMove::leave_();
}

void GanonBeamMove::loadParams_() {
    BeamMove::loadParams_();
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackPowerForPlayer_m, "AttackPowerForPlayer");
    getMapUnitParam(&mPosOffset_m, "PosOffset");
}

void GanonBeamMove::calc_() {
    BeamMove::calc_();
}

}  // namespace uking::action
