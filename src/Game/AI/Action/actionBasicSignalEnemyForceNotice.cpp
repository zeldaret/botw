#include "Game/AI/Action/actionBasicSignalEnemyForceNotice.h"

namespace uking::action {

BasicSignalEnemyForceNotice::BasicSignalEnemyForceNotice(const InitArg& arg)
    : BasicSignalEnemy(arg) {}

BasicSignalEnemyForceNotice::~BasicSignalEnemyForceNotice() = default;

bool BasicSignalEnemyForceNotice::init_(sead::Heap* heap) {
    return BasicSignalEnemy::init_(heap);
}

void BasicSignalEnemyForceNotice::enter_(ksys::act::ai::InlineParamPack* params) {
    BasicSignalEnemy::enter_(params);
}

void BasicSignalEnemyForceNotice::leave_() {
    BasicSignalEnemy::leave_();
}

void BasicSignalEnemyForceNotice::loadParams_() {
    BasicSignalEnemy::loadParams_();
    getStaticParam(&mInterval_s, "Interval");
}

void BasicSignalEnemyForceNotice::calc_() {
    BasicSignalEnemy::calc_();
}

}  // namespace uking::action
