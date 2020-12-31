#include "Game/AI/AI/aiPreyReaction.h"

namespace uking::ai {

PreyReaction::PreyReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyReaction::~PreyReaction() = default;

bool PreyReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PreyReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyReaction::loadParams_() {}

}  // namespace uking::ai
