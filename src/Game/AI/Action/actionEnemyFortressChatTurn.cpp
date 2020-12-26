#include "Game/AI/Action/actionEnemyFortressChatTurn.h"

namespace uking::action {

EnemyFortressChatTurn::EnemyFortressChatTurn(const InitArg& arg) : EnemyFortressChatTurnBase(arg) {}

EnemyFortressChatTurn::~EnemyFortressChatTurn() = default;

bool EnemyFortressChatTurn::init_(sead::Heap* heap) {
    return EnemyFortressChatTurnBase::init_(heap);
}

void EnemyFortressChatTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyFortressChatTurnBase::enter_(params);
}

void EnemyFortressChatTurn::leave_() {
    EnemyFortressChatTurnBase::leave_();
}

void EnemyFortressChatTurn::loadParams_() {
    EnemyFortressChatTurnBase::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void EnemyFortressChatTurn::calc_() {
    EnemyFortressChatTurnBase::calc_();
}

}  // namespace uking::action
