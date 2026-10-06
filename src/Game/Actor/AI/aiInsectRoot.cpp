#include "Game/Actor/AI/aiInsectRoot.h"

namespace uking::ai {

InsectRoot::InsectRoot(const InitArg& arg) : CapturedActorRoot(arg) {}

InsectRoot::~InsectRoot() = default;

bool InsectRoot::init_(sead::Heap* heap) {
    return CapturedActorRoot::init_(heap);
}

void InsectRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    CapturedActorRoot::enter_(params);
}

void InsectRoot::leave_() {
    CapturedActorRoot::leave_();
}

void InsectRoot::loadParams_() {
    CapturedActorRoot::loadParams_();
    getStaticParam(&mIsEscapeInWater_s, "IsEscapeInWater");
}

}  // namespace uking::ai
