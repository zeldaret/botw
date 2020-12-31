#include "Game/AI/AI/aiCapturedActorReaction.h"

namespace uking::ai {

CapturedActorReaction::CapturedActorReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CapturedActorReaction::~CapturedActorReaction() = default;

bool CapturedActorReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CapturedActorReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CapturedActorReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CapturedActorReaction::loadParams_() {}

}  // namespace uking::ai
