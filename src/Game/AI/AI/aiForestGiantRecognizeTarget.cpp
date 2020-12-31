#include "Game/AI/AI/aiForestGiantRecognizeTarget.h"

namespace uking::ai {

ForestGiantRecognizeTarget::ForestGiantRecognizeTarget(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

ForestGiantRecognizeTarget::~ForestGiantRecognizeTarget() = default;

bool ForestGiantRecognizeTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ForestGiantRecognizeTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ForestGiantRecognizeTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ForestGiantRecognizeTarget::loadParams_() {}

}  // namespace uking::ai
