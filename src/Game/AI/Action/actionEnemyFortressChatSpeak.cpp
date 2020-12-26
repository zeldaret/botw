#include "Game/AI/Action/actionEnemyFortressChatSpeak.h"

namespace uking::action {

EnemyFortressChatSpeak::EnemyFortressChatSpeak(const InitArg& arg) : EnemyFortressChatTalk(arg) {}

EnemyFortressChatSpeak::~EnemyFortressChatSpeak() = default;

bool EnemyFortressChatSpeak::init_(sead::Heap* heap) {
    return EnemyFortressChatTalk::init_(heap);
}

void EnemyFortressChatSpeak::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyFortressChatTalk::enter_(params);
}

void EnemyFortressChatSpeak::leave_() {
    EnemyFortressChatTalk::leave_();
}

void EnemyFortressChatSpeak::loadParams_() {
    EnemyFortressChatTalk::loadParams_();
}

void EnemyFortressChatSpeak::calc_() {
    EnemyFortressChatTalk::calc_();
}

}  // namespace uking::action
