#include "Game/AI/AI/aiMoveAroundTarget.h"

namespace uking::ai {

MoveAroundTarget::MoveAroundTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoveAroundTarget::~MoveAroundTarget() = default;

bool MoveAroundTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MoveAroundTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MoveAroundTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoveAroundTarget::loadParams_() {
    getStaticParam(&mTurnTimeBase_s, "TurnTimeBase");
    getStaticParam(&mTurnTimeRand_s, "TurnTimeRand");
    getStaticParam(&mStartRange_s, "StartRange");
    getStaticParam(&mEndRange_s, "EndRange");
    getStaticParam(&mChangeRangeRate_s, "ChangeRangeRate");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
