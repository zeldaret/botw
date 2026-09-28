#include "Game/Actor/AI/aiChildFavoriteSelector.h"

namespace uking::ai {

ChildFavoriteSelector::ChildFavoriteSelector(const InitArg& arg) : ChildSelector(arg) {}

ChildFavoriteSelector::~ChildFavoriteSelector() = default;

bool ChildFavoriteSelector::init_(sead::Heap* heap) {
    return ChildSelector::init_(heap);
}

void ChildFavoriteSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ChildSelector::enter_(params);
}

void ChildFavoriteSelector::leave_() {
    ChildSelector::leave_();
}

void ChildFavoriteSelector::loadParams_() {
    ChildSelector::loadParams_();
}

}  // namespace uking::ai
