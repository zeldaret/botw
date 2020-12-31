#include "Game/AI/AI/aiWeakStateSelecter.h"

namespace uking::ai {

WeakStateSelecter::WeakStateSelecter(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeakStateSelecter::~WeakStateSelecter() = default;

bool WeakStateSelecter::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeakStateSelecter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeakStateSelecter::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeakStateSelecter::loadParams_() {
    getStaticParam(&mIsAlwaysUpdate_s, "IsAlwaysUpdate");
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
}

}  // namespace uking::ai
