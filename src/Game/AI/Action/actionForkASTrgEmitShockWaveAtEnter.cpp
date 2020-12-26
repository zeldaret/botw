#include "Game/AI/Action/actionForkASTrgEmitShockWaveAtEnter.h"

namespace uking::action {

ForkASTrgEmitShockWaveAtEnter::ForkASTrgEmitShockWaveAtEnter(const InitArg& arg)
    : ForkASTrgEmitShockWave(arg) {}

ForkASTrgEmitShockWaveAtEnter::~ForkASTrgEmitShockWaveAtEnter() = default;

bool ForkASTrgEmitShockWaveAtEnter::init_(sead::Heap* heap) {
    return ForkASTrgEmitShockWave::init_(heap);
}

void ForkASTrgEmitShockWaveAtEnter::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASTrgEmitShockWave::enter_(params);
}

void ForkASTrgEmitShockWaveAtEnter::leave_() {
    ForkASTrgEmitShockWave::leave_();
}

void ForkASTrgEmitShockWaveAtEnter::loadParams_() {
    ForkASTrgEmitShockWave::loadParams_();
    getStaticParam(&mOffsetPos_s, "OffsetPos");
}

void ForkASTrgEmitShockWaveAtEnter::calc_() {
    ForkASTrgEmitShockWave::calc_();
}

}  // namespace uking::action
