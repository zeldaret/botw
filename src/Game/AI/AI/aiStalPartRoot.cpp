#include "Game/AI/AI/aiStalPartRoot.h"

namespace uking::ai {

StalPartRoot::StalPartRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalPartRoot::~StalPartRoot() = default;

bool StalPartRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalPartRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalPartRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalPartRoot::loadParams_() {
    getStaticParam(&mInvincibleTime_s, "InvincibleTime");
}

}  // namespace uking::ai
