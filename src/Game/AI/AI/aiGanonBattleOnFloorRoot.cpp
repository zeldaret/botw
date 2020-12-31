#include "Game/AI/AI/aiGanonBattleOnFloorRoot.h"

namespace uking::ai {

GanonBattleOnFloorRoot::GanonBattleOnFloorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBattleOnFloorRoot::~GanonBattleOnFloorRoot() = default;

bool GanonBattleOnFloorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBattleOnFloorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonBattleOnFloorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBattleOnFloorRoot::loadParams_() {
    getStaticParam(&mFarAttackDist_s, "FarAttackDist");
    getDynamicParam(&mIsNoWait_d, "IsNoWait");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
