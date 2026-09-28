#include "Game/Actor/AI/aiChildSelector.h"

namespace uking::ai {

ChildSelector::ChildSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChildSelector::~ChildSelector() = default;

bool ChildSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChildSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ChildSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChildSelector::loadParams_() {
    getStaticParam(&mIsNoChildForceEnd_s, "IsNoChildForceEnd");
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
}

}  // namespace uking::ai
