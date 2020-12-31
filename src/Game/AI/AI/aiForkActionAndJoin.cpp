#include "Game/AI/AI/aiForkActionAndJoin.h"

namespace uking::ai {

ForkActionAndJoin::ForkActionAndJoin(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ForkActionAndJoin::~ForkActionAndJoin() = default;

bool ForkActionAndJoin::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ForkActionAndJoin::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ForkActionAndJoin::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ForkActionAndJoin::loadParams_() {}

}  // namespace uking::ai
