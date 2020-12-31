#include "Game/AI/AI/aiStalPartCatch.h"

namespace uking::ai {

StalPartCatch::StalPartCatch(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalPartCatch::~StalPartCatch() = default;

bool StalPartCatch::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalPartCatch::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalPartCatch::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalPartCatch::loadParams_() {}

}  // namespace uking::ai
