#include "Game/AI/AI/aiAroundEnemyCheckSelect.h"

namespace uking::ai {

AroundEnemyCheckSelect::AroundEnemyCheckSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AroundEnemyCheckSelect::~AroundEnemyCheckSelect() = default;

void AroundEnemyCheckSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AroundEnemyCheckSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AroundEnemyCheckSelect::loadParams_() {
    getStaticParam(&mCheckDist_s, "CheckDist");
}

}  // namespace uking::ai
