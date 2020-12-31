#include "Game/AI/AI/aiLynelChaseBattleMove.h"

namespace uking::ai {

LynelChaseBattleMove::LynelChaseBattleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelChaseBattleMove::~LynelChaseBattleMove() = default;

bool LynelChaseBattleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelChaseBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelChaseBattleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelChaseBattleMove::loadParams_() {
    getStaticParam(&mSlowDownDist_s, "SlowDownDist");
    getStaticParam(&mSpeedUpDist_s, "SpeedUpDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mCloseStartDist_s, "CloseStartDist");
}

}  // namespace uking::ai
