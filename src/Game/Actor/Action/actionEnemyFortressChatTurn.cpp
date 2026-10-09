#include "Game/Actor/Action/actionEnemyFortressChatTurn.h"

namespace uking::action {

EnemyFortressChatTurn::EnemyFortressChatTurn(const InitArg& arg) : EnemyFortressChatLookBase(arg) {}

EnemyFortressChatTurn::~EnemyFortressChatTurn() = default;

bool EnemyFortressChatTurn::init_(sead::Heap* heap) {
    return EnemyFortressChatLookBase::init_(heap);
}

void EnemyFortressChatTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyFortressChatLookBase::enter_(params);
}

void EnemyFortressChatTurn::leave_() {
    EnemyFortressChatLookBase::leave_();
}

void EnemyFortressChatTurn::loadParams_() {
    EnemyFortressChatLookBase::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void EnemyFortressChatTurn::calc_() {
    EnemyFortressChatLookBase::calc_();
}

}  // namespace uking::action
