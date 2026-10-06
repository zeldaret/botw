#include "Game/Actor/Action/actionForkASTrgEmitShockWavePos.h"

namespace uking::action {

ForkASTrgEmitShockWavePos::ForkASTrgEmitShockWavePos(const InitArg& arg) : ForkEmitShockWave(arg) {}

ForkASTrgEmitShockWavePos::~ForkASTrgEmitShockWavePos() = default;

bool ForkASTrgEmitShockWavePos::init_(sead::Heap* heap) {
    return ForkEmitShockWave::init_(heap);
}

void ForkASTrgEmitShockWavePos::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitShockWave::enter_(params);
}

void ForkASTrgEmitShockWavePos::leave_() {
    ForkEmitShockWave::leave_();
}

void ForkASTrgEmitShockWavePos::loadParams_() {
    ForkEmitShockWave::loadParams_();
    getStaticParam(&mOffsetPos_s, "OffsetPos");
}

void ForkASTrgEmitShockWavePos::calc_() {
    ForkEmitShockWave::calc_();
}

}  // namespace uking::action
