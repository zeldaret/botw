#include "Game/AI/Action/actionEnemyFortressChatTalk.h"

namespace uking::action {

EnemyFortressChatTalk::EnemyFortressChatTalk(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EnemyFortressChatTalk::~EnemyFortressChatTalk() = default;

bool EnemyFortressChatTalk::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EnemyFortressChatTalk::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EnemyFortressChatTalk::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnemyFortressChatTalk::loadParams_() {
    getStaticParam(&mTryNum_s, "TryNum");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getStaticParam(&mTimeOut_s, "TimeOut");
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

void EnemyFortressChatTalk::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
