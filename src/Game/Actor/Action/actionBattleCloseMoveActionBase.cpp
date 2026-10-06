#include "Game/Actor/Action/actionBattleCloseMoveActionBase.h"

namespace uking::action {

BattleCloseMoveActionBase::BattleCloseMoveActionBase(const InitArg& arg)
    : AvoidingCloseMoveBase(arg) {}

BattleCloseMoveActionBase::~BattleCloseMoveActionBase() = default;

bool BattleCloseMoveActionBase::init_(sead::Heap* heap) {
    return AvoidingCloseMoveBase::init_(heap);
}

void BattleCloseMoveActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    AvoidingCloseMoveBase::enter_(params);
}

void BattleCloseMoveActionBase::leave_() {
    AvoidingCloseMoveBase::leave_();
}

void BattleCloseMoveActionBase::loadParams_() {
    AvoidingCloseMoveBase::loadParams_();
}

void BattleCloseMoveActionBase::calc_() {
    AvoidingCloseMoveBase::calc_();
}

}  // namespace uking::action
