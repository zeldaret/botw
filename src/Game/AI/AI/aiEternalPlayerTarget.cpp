#include "Game/AI/AI/aiEternalPlayerTarget.h"

namespace uking::ai {

EternalPlayerTarget::EternalPlayerTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EternalPlayerTarget::~EternalPlayerTarget() = default;

bool EternalPlayerTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EternalPlayerTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EternalPlayerTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EternalPlayerTarget::loadParams_() {}

}  // namespace uking::ai
