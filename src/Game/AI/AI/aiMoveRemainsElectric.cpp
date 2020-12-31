#include "Game/AI/AI/aiMoveRemainsElectric.h"

namespace uking::ai {

MoveRemainsElectric::MoveRemainsElectric(const InitArg& arg) : RailMoveRemains(arg) {}

MoveRemainsElectric::~MoveRemainsElectric() = default;

bool MoveRemainsElectric::init_(sead::Heap* heap) {
    return RailMoveRemains::init_(heap);
}

void MoveRemainsElectric::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveRemains::enter_(params);
}

void MoveRemainsElectric::leave_() {
    RailMoveRemains::leave_();
}

void MoveRemainsElectric::loadParams_() {
    RailMoveRemains::loadParams_();
    getStaticParam(&mReactiveRange_s, "ReactiveRange");
    getStaticParam(&mDemoCallWaitTime_s, "DemoCallWaitTime");
    getStaticParam(&mCannonOffset_s, "CannonOffset");
    getStaticParam(&mWeakPointOffset_s, "WeakPointOffset");
    getMapUnitParam(&mIsJoinRemainsBattle_m, "IsJoinRemainsBattle");
}

}  // namespace uking::ai
