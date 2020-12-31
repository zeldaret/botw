#include "Game/AI/AI/aiOctarockOptionRoot.h"

namespace uking::ai {

OctarockOptionRoot::OctarockOptionRoot(const InitArg& arg) : SimpleLiftable(arg) {}

OctarockOptionRoot::~OctarockOptionRoot() = default;

bool OctarockOptionRoot::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

void OctarockOptionRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
}

void OctarockOptionRoot::leave_() {
    SimpleLiftable::leave_();
}

void OctarockOptionRoot::loadParams_() {
    getStaticParam(&mIsBreakable_s, "IsBreakable");
    getStaticParam(&mIsMimicry_s, "IsMimicry");
}

}  // namespace uking::ai
