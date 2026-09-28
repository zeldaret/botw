#include "Game/Actor/Action/actionBasicSignalEnemyForceNotice.h"

namespace uking::action {

BasicSignalEnemyForceNotice::BasicSignalEnemyForceNotice(const InitArg& arg)
    : BasicSignalEnemyNotice(arg) {}

BasicSignalEnemyForceNotice::~BasicSignalEnemyForceNotice() = default;

bool BasicSignalEnemyForceNotice::init_(sead::Heap* heap) {
    return BasicSignalEnemyNotice::init_(heap);
}

void BasicSignalEnemyForceNotice::enter_(ksys::act::ai::InlineParamPack* params) {
    BasicSignalEnemyNotice::enter_(params);
}

void BasicSignalEnemyForceNotice::leave_() {
    BasicSignalEnemyNotice::leave_();
}

void BasicSignalEnemyForceNotice::loadParams_() {
    BasicSignalEnemyNotice::loadParams_();
    getStaticParam(&mInterval_s, "Interval");
}

void BasicSignalEnemyForceNotice::calc_() {
    BasicSignalEnemyNotice::calc_();
}

}  // namespace uking::action
