#include "Game/AI/AI/aiReferenceNPCViewWithDynAS.h"

namespace uking::ai {

ReferenceNPCViewWithDynAS::ReferenceNPCViewWithDynAS(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReferenceNPCViewWithDynAS::~ReferenceNPCViewWithDynAS() = default;

bool ReferenceNPCViewWithDynAS::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReferenceNPCViewWithDynAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ReferenceNPCViewWithDynAS::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ReferenceNPCViewWithDynAS::loadParams_() {
    getDynamicParam(&mDynASKey_d, "DynASKey");
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
    getStaticParam(&mCheckOnce_s, "CheckOnce");
    getDynamicParam(&mDynASKey_d, "DynASKey");
}

}  // namespace uking::ai
