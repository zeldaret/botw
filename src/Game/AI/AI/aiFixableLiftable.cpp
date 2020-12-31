#include "Game/AI/AI/aiFixableLiftable.h"

namespace uking::ai {

FixableLiftable::FixableLiftable(const InitArg& arg) : SimpleLiftable(arg) {}

FixableLiftable::~FixableLiftable() = default;

bool FixableLiftable::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

void FixableLiftable::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
}

void FixableLiftable::leave_() {
    SimpleLiftable::leave_();
}

void FixableLiftable::loadParams_() {
    getStaticParam(&mCancelFixedScale_s, "CancelFixedScale");
    getMapUnitParam(&mIsFixedPlace_m, "IsFixedPlace");
}

}  // namespace uking::ai
