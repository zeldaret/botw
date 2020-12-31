#include "Game/AI/AI/aiWolfLinkReaction.h"

namespace uking::ai {

WolfLinkReaction::WolfLinkReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkReaction::~WolfLinkReaction() = default;

bool WolfLinkReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkReaction::loadParams_() {}

}  // namespace uking::ai
