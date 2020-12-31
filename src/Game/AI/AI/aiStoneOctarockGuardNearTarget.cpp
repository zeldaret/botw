#include "Game/AI/AI/aiStoneOctarockGuardNearTarget.h"

namespace uking::ai {

StoneOctarockGuardNearTarget::StoneOctarockGuardNearTarget(const InitArg& arg)
    : TimedGuardNearTarget(arg) {}

StoneOctarockGuardNearTarget::~StoneOctarockGuardNearTarget() = default;

bool StoneOctarockGuardNearTarget::init_(sead::Heap* heap) {
    return TimedGuardNearTarget::init_(heap);
}

void StoneOctarockGuardNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    TimedGuardNearTarget::enter_(params);
}

void StoneOctarockGuardNearTarget::leave_() {
    TimedGuardNearTarget::leave_();
}

void StoneOctarockGuardNearTarget::loadParams_() {
    TimedGuardNearTarget::loadParams_();
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
}

}  // namespace uking::ai
