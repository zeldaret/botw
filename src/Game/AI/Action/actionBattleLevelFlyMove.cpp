#include "Game/AI/Action/actionBattleLevelFlyMove.h"

namespace uking::action {

BattleLevelFlyMove::BattleLevelFlyMove(const InitArg& arg) : BattleLevelFlyMoveBase(arg) {}

BattleLevelFlyMove::~BattleLevelFlyMove() = default;

bool BattleLevelFlyMove::init_(sead::Heap* heap) {
    return BattleLevelFlyMoveBase::init_(heap);
}

void BattleLevelFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleLevelFlyMoveBase::enter_(params);
}

void BattleLevelFlyMove::leave_() {
    BattleLevelFlyMoveBase::leave_();
}

void BattleLevelFlyMove::loadParams_() {
    BattleLevelFlyMoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void BattleLevelFlyMove::calc_() {
    BattleLevelFlyMoveBase::calc_();
}

}  // namespace uking::action
