#include "Game/AI/AI/aiItemRoot.h"

namespace uking::ai {

ItemRoot::ItemRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ItemRoot::~ItemRoot() = default;

bool ItemRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ItemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ItemRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ItemRoot::loadParams_() {
    getStaticParam(&mAtHitImpulseRate_s, "AtHitImpulseRate");
    getMapUnitParam(&mInitMotionStatus_m, "InitMotionStatus");
}

}  // namespace uking::ai
