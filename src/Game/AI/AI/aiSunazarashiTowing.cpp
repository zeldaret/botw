#include "Game/AI/AI/aiSunazarashiTowing.h"

namespace uking::ai {

SunazarashiTowing::SunazarashiTowing(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SunazarashiTowing::~SunazarashiTowing() = default;

bool SunazarashiTowing::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SunazarashiTowing::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SunazarashiTowing::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SunazarashiTowing::loadParams_() {}

}  // namespace uking::ai
