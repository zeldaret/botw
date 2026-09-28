#include "Game/Actor/Action/actionEnemyFortressChatLookBase.h"

namespace uking::action {

EnemyFortressChatLookBase::EnemyFortressChatLookBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EnemyFortressChatLookBase::~EnemyFortressChatLookBase() = default;

bool EnemyFortressChatLookBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EnemyFortressChatLookBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EnemyFortressChatLookBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnemyFortressChatLookBase::loadParams_() {
    getStaticParam(&mTryNum_s, "TryNum");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

void EnemyFortressChatLookBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
