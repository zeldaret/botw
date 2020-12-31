#include "Game/AI/AI/aiForkBeastGanonRoot.h"

namespace uking::ai {

ForkBeastGanonRoot::ForkBeastGanonRoot(const InitArg& arg) : ForkAI(arg) {}

ForkBeastGanonRoot::~ForkBeastGanonRoot() = default;

bool ForkBeastGanonRoot::init_(sead::Heap* heap) {
    return ForkAI::init_(heap);
}

void ForkBeastGanonRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAI::enter_(params);
}

void ForkBeastGanonRoot::leave_() {
    ForkAI::leave_();
}

void ForkBeastGanonRoot::loadParams_() {}

}  // namespace uking::ai
