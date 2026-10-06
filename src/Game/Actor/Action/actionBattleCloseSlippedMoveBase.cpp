#include "Game/Actor/Action/actionBattleCloseSlippedMoveBase.h"

namespace uking::action {

BattleCloseSlippedMoveBase::BattleCloseSlippedMoveBase(const InitArg& arg)
    : AvoidingCloseMoveActionWithAcc(arg) {}

BattleCloseSlippedMoveBase::~BattleCloseSlippedMoveBase() = default;

bool BattleCloseSlippedMoveBase::init_(sead::Heap* heap) {
    return AvoidingCloseMoveActionWithAcc::init_(heap);
}

void BattleCloseSlippedMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    AvoidingCloseMoveActionWithAcc::enter_(params);
}

void BattleCloseSlippedMoveBase::leave_() {
    AvoidingCloseMoveActionWithAcc::leave_();
}

void BattleCloseSlippedMoveBase::loadParams_() {
    AvoidingCloseMoveActionWithAcc::loadParams_();
}

void BattleCloseSlippedMoveBase::calc_() {
    AvoidingCloseMoveActionWithAcc::calc_();
}

}  // namespace uking::action
