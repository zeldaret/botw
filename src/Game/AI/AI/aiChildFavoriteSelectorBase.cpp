#include "Game/AI/AI/aiChildFavoriteSelectorBase.h"

namespace uking::ai {

ChildFavoriteSelectorBase::ChildFavoriteSelectorBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChildFavoriteSelectorBase::~ChildFavoriteSelectorBase() = default;

bool ChildFavoriteSelectorBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChildFavoriteSelectorBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ChildFavoriteSelectorBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChildFavoriteSelectorBase::loadParams_() {
    getStaticParam(&mIsNoChildForceEnd_s, "IsNoChildForceEnd");
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
}

}  // namespace uking::ai
