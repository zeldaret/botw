#include "Game/AI/AI/aiGanonBattleOnWallRoot.h"

namespace uking::ai {

GanonBattleOnWallRoot::GanonBattleOnWallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBattleOnWallRoot::~GanonBattleOnWallRoot() = default;

bool GanonBattleOnWallRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBattleOnWallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonBattleOnWallRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBattleOnWallRoot::loadParams_() {
    getStaticParam(&mGuardianActivateHP_s, "GuardianActivateHP");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
