#include "Game/Actor/Action/actionBattleCloseSlippedWalk.h"

namespace uking::action {

BattleCloseSlippedWalk::BattleCloseSlippedWalk(const InitArg& arg)
    : BattleCloseSlippedMoveBase(arg) {}

BattleCloseSlippedWalk::~BattleCloseSlippedWalk() = default;

bool BattleCloseSlippedWalk::init_(sead::Heap* heap) {
    return BattleCloseSlippedMoveBase::init_(heap);
}

void BattleCloseSlippedWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseSlippedMoveBase::enter_(params);
}

void BattleCloseSlippedWalk::leave_() {
    BattleCloseSlippedMoveBase::leave_();
}

void BattleCloseSlippedWalk::loadParams_() {
    BattleCloseSlippedMoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void BattleCloseSlippedWalk::calc_() {
    BattleCloseSlippedMoveBase::calc_();
}

}  // namespace uking::action
