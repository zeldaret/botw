#include "Game/AI/AI/aiGanonBeastReaction.h"

namespace uking::ai {

GanonBeastReaction::GanonBeastReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastReaction::~GanonBeastReaction() = default;

bool GanonBeastReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBeastReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonBeastReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBeastReaction::loadParams_() {
    getStaticParam(&mASSlot_s, "ASSlot");
    getAITreeVariable(&mWeakPointAliveFlag_a, "WeakPointAliveFlag");
    getAITreeVariable(&mWeakPointActiveFlag_a, "WeakPointActiveFlag");
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
}

}  // namespace uking::ai
