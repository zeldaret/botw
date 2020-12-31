#include "Game/AI/AI/aiWeakPointRoot.h"

namespace uking::ai {

WeakPointRoot::WeakPointRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeakPointRoot::~WeakPointRoot() = default;

bool WeakPointRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeakPointRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeakPointRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeakPointRoot::loadParams_() {
    getStaticParam(&mOwnerDamage_s, "OwnerDamage");
    getStaticParam(&mIsBreakable_s, "IsBreakable");
    getStaticParam(&mIsSyncDamage_s, "IsSyncDamage");
    getStaticParam(&mIsShowCriticalEffect_s, "IsShowCriticalEffect");
    getStaticParam(&mIsNoReaction_s, "IsNoReaction");
}

}  // namespace uking::ai
