#include "Game/AI/AI/aiGiantEscapeFromDamageWater.h"

namespace uking::ai {

GiantEscapeFromDamageWater::GiantEscapeFromDamageWater(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GiantEscapeFromDamageWater::~GiantEscapeFromDamageWater() = default;

bool GiantEscapeFromDamageWater::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GiantEscapeFromDamageWater::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GiantEscapeFromDamageWater::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantEscapeFromDamageWater::loadParams_() {}

}  // namespace uking::ai
