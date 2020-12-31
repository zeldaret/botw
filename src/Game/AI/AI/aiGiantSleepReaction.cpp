#include "Game/AI/AI/aiGiantSleepReaction.h"

namespace uking::ai {

GiantSleepReaction::GiantSleepReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GiantSleepReaction::~GiantSleepReaction() = default;

bool GiantSleepReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GiantSleepReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GiantSleepReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantSleepReaction::loadParams_() {}

}  // namespace uking::ai
