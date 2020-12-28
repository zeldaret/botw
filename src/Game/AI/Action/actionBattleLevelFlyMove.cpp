#include "Game/AI/Action/actionBattleLevelFlyMove.h"

namespace uking::action {

BattleLevelFlyMove::BattleLevelFlyMove(const InitArg& arg) : BattleLevelFlyMoveBase(arg) {}

BattleLevelFlyMove::~BattleLevelFlyMove() = default;

void BattleLevelFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleLevelFlyMoveBase::enter_(params);
}

void BattleLevelFlyMove::loadParams_() {
    BattleLevelFlyMoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
