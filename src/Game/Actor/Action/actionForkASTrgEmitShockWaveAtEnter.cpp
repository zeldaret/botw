#include "Game/Actor/Action/actionForkASTrgEmitShockWaveAtEnter.h"

namespace uking::action {

ForkASTrgEmitShockWaveAtEnter::ForkASTrgEmitShockWaveAtEnter(const InitArg& arg)
    : ForkEmitShockWave(arg) {}

ForkASTrgEmitShockWaveAtEnter::~ForkASTrgEmitShockWaveAtEnter() = default;

bool ForkASTrgEmitShockWaveAtEnter::init_(sead::Heap* heap) {
    return ForkEmitShockWave::init_(heap);
}

void ForkASTrgEmitShockWaveAtEnter::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitShockWave::enter_(params);
}

void ForkASTrgEmitShockWaveAtEnter::leave_() {
    ForkEmitShockWave::leave_();
}

void ForkASTrgEmitShockWaveAtEnter::loadParams_() {
    ForkEmitShockWave::loadParams_();
    getStaticParam(&mOffsetPos_s, "OffsetPos");
}

void ForkASTrgEmitShockWaveAtEnter::calc_() {
    ForkEmitShockWave::calc_();
}

}  // namespace uking::action
