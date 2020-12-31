#include "Game/AI/AI/aiAncientNecklaceBallBase.h"

namespace uking::ai {

AncientNecklaceBallBase::AncientNecklaceBallBase(const InitArg& arg) : SimpleLiftable(arg) {}

AncientNecklaceBallBase::~AncientNecklaceBallBase() = default;

bool AncientNecklaceBallBase::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

void AncientNecklaceBallBase::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
}

void AncientNecklaceBallBase::leave_() {
    SimpleLiftable::leave_();
}

void AncientNecklaceBallBase::loadParams_() {
    getStaticParam(&mIsIgnoreSameOnAS_s, "IsIgnoreSameOnAS");
    getStaticParam(&mIsIgnoreSameOffAS_s, "IsIgnoreSameOffAS");
    getStaticParam(&mOnAS_s, "OnAS");
    getStaticParam(&mOffAS_s, "OffAS");
}

}  // namespace uking::ai
