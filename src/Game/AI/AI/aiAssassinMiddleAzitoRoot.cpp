#include "Game/AI/AI/aiAssassinMiddleAzitoRoot.h"

namespace uking::ai {

AssassinMiddleAzitoRoot::AssassinMiddleAzitoRoot(const InitArg& arg) : AssassinNormal(arg) {}

AssassinMiddleAzitoRoot::~AssassinMiddleAzitoRoot() = default;

bool AssassinMiddleAzitoRoot::init_(sead::Heap* heap) {
    return AssassinNormal::init_(heap);
}

void AssassinMiddleAzitoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinNormal::enter_(params);
}

void AssassinMiddleAzitoRoot::leave_() {
    AssassinNormal::leave_();
}

void AssassinMiddleAzitoRoot::loadParams_() {
    AssassinNormal::loadParams_();
    getStaticParam(&mEntryPoint_s, "EntryPoint");
    getStaticParam(&mDemoName_s, "DemoName");
    getStaticParam(&mLikeItem_s, "LikeItem");
}

}  // namespace uking::ai
