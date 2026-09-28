#include "Game/Actor/AI/aiAssassinMiddleAzitoRoot.h"

namespace uking::ai {

AssassinMiddleAzitoRoot::AssassinMiddleAzitoRoot(const InitArg& arg) : GuardHomePosNormal(arg) {}

AssassinMiddleAzitoRoot::~AssassinMiddleAzitoRoot() = default;

bool AssassinMiddleAzitoRoot::init_(sead::Heap* heap) {
    return GuardHomePosNormal::init_(heap);
}

void AssassinMiddleAzitoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardHomePosNormal::enter_(params);
}

void AssassinMiddleAzitoRoot::leave_() {
    GuardHomePosNormal::leave_();
}

void AssassinMiddleAzitoRoot::loadParams_() {
    GuardHomePosNormal::loadParams_();
    getStaticParam(&mEntryPoint_s, "EntryPoint");
    getStaticParam(&mDemoName_s, "DemoName");
    getStaticParam(&mLikeItem_s, "LikeItem");
}

}  // namespace uking::ai
