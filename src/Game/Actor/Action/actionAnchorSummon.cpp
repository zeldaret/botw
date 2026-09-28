#include "Game/Actor/Action/actionAnchorSummon.h"

namespace uking::action {

AnchorSummon::AnchorSummon(const InitArg& arg) : StopBase(arg) {}

AnchorSummon::~AnchorSummon() = default;

bool AnchorSummon::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void AnchorSummon::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void AnchorSummon::leave_() {
    StopBase::leave_();
}

void AnchorSummon::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mSummonActor_d, "SummonActor");
    getDynamicParam(&mSummonActorEquip1_d, "SummonActorEquip1");
    getDynamicParam(&mSummonActorEquip2_d, "SummonActorEquip2");
}

void AnchorSummon::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
