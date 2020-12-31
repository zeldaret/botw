#include "Game/AI/AI/aiChildFavoriteSelector.h"

namespace uking::ai {

ChildFavoriteSelector::ChildFavoriteSelector(const InitArg& arg) : ChildFavoriteSelectorBase(arg) {}

ChildFavoriteSelector::~ChildFavoriteSelector() = default;

bool ChildFavoriteSelector::init_(sead::Heap* heap) {
    return ChildFavoriteSelectorBase::init_(heap);
}

void ChildFavoriteSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ChildFavoriteSelectorBase::enter_(params);
}

void ChildFavoriteSelector::leave_() {
    ChildFavoriteSelectorBase::leave_();
}

void ChildFavoriteSelector::loadParams_() {
    ChildFavoriteSelectorBase::loadParams_();
}

}  // namespace uking::ai
