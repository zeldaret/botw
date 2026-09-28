#include "Game/Actor/Action/actionBasicSignalBossAwakeSleep.h"

namespace uking::action {

BasicSignalBossAwakeSleep::BasicSignalBossAwakeSleep(const InitArg& arg)
    : BasicSignalEnemyNotice(arg) {}

BasicSignalBossAwakeSleep::~BasicSignalBossAwakeSleep() = default;

bool BasicSignalBossAwakeSleep::init_(sead::Heap* heap) {
    return BasicSignalEnemyNotice::init_(heap);
}

void BasicSignalBossAwakeSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    BasicSignalEnemyNotice::enter_(params);
}

void BasicSignalBossAwakeSleep::leave_() {
    BasicSignalEnemyNotice::leave_();
}

void BasicSignalBossAwakeSleep::loadParams_() {
    BasicSignalEnemyNotice::loadParams_();
}

void BasicSignalBossAwakeSleep::calc_() {
    BasicSignalEnemyNotice::calc_();
}

}  // namespace uking::action
