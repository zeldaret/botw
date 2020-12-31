#include "Game/AI/AI/aiSwarmReaction.h"

namespace uking::ai {

SwarmReaction::SwarmReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwarmReaction::~SwarmReaction() = default;

bool SwarmReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwarmReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwarmReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwarmReaction::loadParams_() {}

}  // namespace uking::ai
