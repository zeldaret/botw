#include "Game/AI/Action/actionBattleCloseSlippedWalkBase.h"

namespace uking::action {

BattleCloseSlippedWalkBase::BattleCloseSlippedWalkBase(const InitArg& arg)
    : BattleCloseActionWithAcc(arg) {}

BattleCloseSlippedWalkBase::~BattleCloseSlippedWalkBase() = default;

bool BattleCloseSlippedWalkBase::init_(sead::Heap* heap) {
    return BattleCloseActionWithAcc::init_(heap);
}

void BattleCloseSlippedWalkBase::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseActionWithAcc::enter_(params);
}

void BattleCloseSlippedWalkBase::leave_() {
    BattleCloseActionWithAcc::leave_();
}

void BattleCloseSlippedWalkBase::loadParams_() {
    BattleCloseActionWithAcc::loadParams_();
}

void BattleCloseSlippedWalkBase::calc_() {
    BattleCloseActionWithAcc::calc_();
}

}  // namespace uking::action
