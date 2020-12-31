#include "Game/AI/AI/aiBowEquiped.h"

namespace uking::ai {

BowEquiped::BowEquiped(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BowEquiped::~BowEquiped() = default;

void BowEquiped::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BowEquiped::leave_() {
    ksys::act::ai::Ai::leave_();
}

}  // namespace uking::ai
