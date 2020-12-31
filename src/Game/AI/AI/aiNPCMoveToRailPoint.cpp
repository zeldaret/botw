#include "Game/AI/AI/aiNPCMoveToRailPoint.h"

namespace uking::ai {

NPCMoveToRailPoint::NPCMoveToRailPoint(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCMoveToRailPoint::~NPCMoveToRailPoint() = default;

bool NPCMoveToRailPoint::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCMoveToRailPoint::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCMoveToRailPoint::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCMoveToRailPoint::loadParams_() {
    getDynamicParam(&mRailPointIndex_d, "RailPointIndex");
    getDynamicParam(&mIsTurnToRailPointDir_d, "IsTurnToRailPointDir");
    getDynamicParam(&mIsAlignmentAnchor_d, "IsAlignmentAnchor");
    getDynamicParam(&mRailUniqueName_d, "RailUniqueName");
    getDynamicParam(&mASName_d, "ASName");
}

}  // namespace uking::ai
