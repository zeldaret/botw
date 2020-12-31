#include "Game/AI/AI/aiConditionMoveActionSelect.h"

namespace uking::ai {

ConditionMoveActionSelect::ConditionMoveActionSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ConditionMoveActionSelect::~ConditionMoveActionSelect() = default;

bool ConditionMoveActionSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ConditionMoveActionSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ConditionMoveActionSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ConditionMoveActionSelect::loadParams_() {
    getStaticParam(&mCheckLineReachable_s, "CheckLineReachable");
    getDynamicParam(&mDistanceKept_d, "DistanceKept");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
