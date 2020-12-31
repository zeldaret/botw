#include "Game/AI/AI/aiBeeSwarmReaction.h"

namespace uking::ai {

BeeSwarmReaction::BeeSwarmReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BeeSwarmReaction::~BeeSwarmReaction() = default;

bool BeeSwarmReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BeeSwarmReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BeeSwarmReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BeeSwarmReaction::loadParams_() {}

}  // namespace uking::ai
