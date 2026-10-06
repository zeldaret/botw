#include "Game/Actor/AI/aiStoneOctarockGuardNearTarget.h"

namespace uking::ai {

StoneOctarockGuardNearTarget::StoneOctarockGuardNearTarget(const InitArg& arg)
    : InvincibleNearTarget(arg) {}

StoneOctarockGuardNearTarget::~StoneOctarockGuardNearTarget() = default;

bool StoneOctarockGuardNearTarget::init_(sead::Heap* heap) {
    return InvincibleNearTarget::init_(heap);
}

void StoneOctarockGuardNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    InvincibleNearTarget::enter_(params);
}

void StoneOctarockGuardNearTarget::leave_() {
    InvincibleNearTarget::leave_();
}

void StoneOctarockGuardNearTarget::loadParams_() {
    InvincibleNearTarget::loadParams_();
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
}

}  // namespace uking::ai
