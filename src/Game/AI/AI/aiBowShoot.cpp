#include "Game/AI/AI/aiBowShoot.h"

namespace uking::ai {

BowShoot::BowShoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BowShoot::~BowShoot() = default;

void BowShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BowShoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

}  // namespace uking::ai
