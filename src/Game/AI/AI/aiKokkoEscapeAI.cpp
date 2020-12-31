#include "Game/AI/AI/aiKokkoEscapeAI.h"

namespace uking::ai {

KokkoEscapeAI::KokkoEscapeAI(const InitArg& arg) : AnimalEscapeAI(arg) {}

KokkoEscapeAI::~KokkoEscapeAI() = default;

bool KokkoEscapeAI::init_(sead::Heap* heap) {
    return AnimalEscapeAI::init_(heap);
}

void KokkoEscapeAI::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalEscapeAI::enter_(params);
}

void KokkoEscapeAI::leave_() {
    AnimalEscapeAI::leave_();
}

void KokkoEscapeAI::loadParams_() {
    AnimalEscapeAI::loadParams_();
}

}  // namespace uking::ai
