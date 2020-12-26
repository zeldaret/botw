#include "Game/AI/Action/actionSpreadToEnemy.h"

namespace uking::action {

SpreadToEnemy::SpreadToEnemy(const InitArg& arg) : OnetimeStopASPlay(arg) {}

SpreadToEnemy::~SpreadToEnemy() = default;

bool SpreadToEnemy::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void SpreadToEnemy::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void SpreadToEnemy::leave_() {
    OnetimeStopASPlay::leave_();
}

void SpreadToEnemy::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mSpreadDist_s, "SpreadDist");
}

void SpreadToEnemy::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
