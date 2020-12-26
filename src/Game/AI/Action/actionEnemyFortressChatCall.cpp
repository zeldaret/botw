#include "Game/AI/Action/actionEnemyFortressChatCall.h"

namespace uking::action {

EnemyFortressChatCall::EnemyFortressChatCall(const InitArg& arg) : EnemyFortressChatTalk(arg) {}

EnemyFortressChatCall::~EnemyFortressChatCall() = default;

bool EnemyFortressChatCall::init_(sead::Heap* heap) {
    return EnemyFortressChatTalk::init_(heap);
}

void EnemyFortressChatCall::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyFortressChatTalk::enter_(params);
}

void EnemyFortressChatCall::leave_() {
    EnemyFortressChatTalk::leave_();
}

void EnemyFortressChatCall::loadParams_() {
    EnemyFortressChatTalk::loadParams_();
}

void EnemyFortressChatCall::calc_() {
    EnemyFortressChatTalk::calc_();
}

}  // namespace uking::action
