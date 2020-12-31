#include "Game/AI/AI/aiForkAI.h"

namespace uking::ai {

ForkAI::ForkAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ForkAI::~ForkAI() = default;

bool ForkAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ForkAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ForkAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

}  // namespace uking::ai
