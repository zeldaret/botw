#include "Game/AI/Action/actionForkASTrgEmitShockWavePos.h"

namespace uking::action {

ForkASTrgEmitShockWavePos::ForkASTrgEmitShockWavePos(const InitArg& arg)
    : ForkASTrgEmitShockWave(arg) {}

ForkASTrgEmitShockWavePos::~ForkASTrgEmitShockWavePos() = default;

bool ForkASTrgEmitShockWavePos::init_(sead::Heap* heap) {
    return ForkASTrgEmitShockWave::init_(heap);
}

void ForkASTrgEmitShockWavePos::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASTrgEmitShockWave::enter_(params);
}

void ForkASTrgEmitShockWavePos::leave_() {
    ForkASTrgEmitShockWave::leave_();
}

void ForkASTrgEmitShockWavePos::loadParams_() {
    ForkASTrgEmitShockWave::loadParams_();
    getStaticParam(&mOffsetPos_s, "OffsetPos");
}

void ForkASTrgEmitShockWavePos::calc_() {
    ForkASTrgEmitShockWave::calc_();
}

}  // namespace uking::action
