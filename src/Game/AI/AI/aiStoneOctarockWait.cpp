#include "Game/AI/AI/aiStoneOctarockWait.h"

namespace uking::ai {

StoneOctarockWait::StoneOctarockWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StoneOctarockWait::~StoneOctarockWait() = default;

bool StoneOctarockWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StoneOctarockWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StoneOctarockWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StoneOctarockWait::loadParams_() {
    getStaticParam(&mGuardEndTime_s, "GuardEndTime");
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
}

}  // namespace uking::ai
