#include "Game/AI/Action/actionAnchorSummon.h"

namespace uking::action {

AnchorSummon::AnchorSummon(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

AnchorSummon::~AnchorSummon() = default;

bool AnchorSummon::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void AnchorSummon::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void AnchorSummon::leave_() {
    ActionWithPosAngReduce::leave_();
}

void AnchorSummon::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mSummonActor_d, "SummonActor");
    getDynamicParam(&mSummonActorEquip1_d, "SummonActorEquip1");
    getDynamicParam(&mSummonActorEquip2_d, "SummonActorEquip2");
}

void AnchorSummon::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
