#include "Game/AI/Action/actionEnemyFortressChatTurnBase.h"

namespace uking::action {

EnemyFortressChatTurnBase::EnemyFortressChatTurnBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EnemyFortressChatTurnBase::~EnemyFortressChatTurnBase() = default;

bool EnemyFortressChatTurnBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EnemyFortressChatTurnBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EnemyFortressChatTurnBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnemyFortressChatTurnBase::loadParams_() {
    getStaticParam(&mTryNum_s, "TryNum");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

void EnemyFortressChatTurnBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
