#include "Game/AI/AI/aiViewChaseSound.h"

namespace uking::ai {

ViewChaseSound::ViewChaseSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ViewChaseSound::~ViewChaseSound() = default;

bool ViewChaseSound::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ViewChaseSound::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ViewChaseSound::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ViewChaseSound::loadParams_() {
    getStaticParam(&mTurnDir_s, "TurnDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
