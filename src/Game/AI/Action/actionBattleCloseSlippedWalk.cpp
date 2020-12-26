#include "Game/AI/Action/actionBattleCloseSlippedWalk.h"

namespace uking::action {

BattleCloseSlippedWalk::BattleCloseSlippedWalk(const InitArg& arg)
    : BattleCloseSlippedWalkBase(arg) {}

BattleCloseSlippedWalk::~BattleCloseSlippedWalk() = default;

bool BattleCloseSlippedWalk::init_(sead::Heap* heap) {
    return BattleCloseSlippedWalkBase::init_(heap);
}

void BattleCloseSlippedWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseSlippedWalkBase::enter_(params);
}

void BattleCloseSlippedWalk::leave_() {
    BattleCloseSlippedWalkBase::leave_();
}

void BattleCloseSlippedWalk::loadParams_() {
    BattleCloseSlippedWalkBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void BattleCloseSlippedWalk::calc_() {
    BattleCloseSlippedWalkBase::calc_();
}

}  // namespace uking::action
