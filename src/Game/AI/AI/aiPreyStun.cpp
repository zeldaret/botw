#include "Game/AI/AI/aiPreyStun.h"

namespace uking::ai {

PreyStun::PreyStun(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyStun::~PreyStun() = default;

bool PreyStun::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyStun::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PreyStun::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyStun::loadParams_() {
    getStaticParam(&mStunTime_s, "StunTime");
}

}  // namespace uking::ai
