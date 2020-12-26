#include "Game/AI/Action/actionEnemyFortressSimpleAction.h"

namespace uking::action {

EnemyFortressSimpleAction::EnemyFortressSimpleAction(const InitArg& arg) : ForkTimer(arg) {}

EnemyFortressSimpleAction::~EnemyFortressSimpleAction() = default;

bool EnemyFortressSimpleAction::init_(sead::Heap* heap) {
    return ForkTimer::init_(heap);
}

void EnemyFortressSimpleAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTimer::enter_(params);
}

void EnemyFortressSimpleAction::leave_() {
    ForkTimer::leave_();
}

void EnemyFortressSimpleAction::loadParams_() {
    ForkTimer::loadParams_();
    getStaticParam(&mNoRequestTime_s, "NoRequestTime");
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

void EnemyFortressSimpleAction::calc_() {
    ForkTimer::calc_();
}

}  // namespace uking::action
