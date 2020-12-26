#include "Game/AI/Action/actionForkSeparateThreeASPart.h"

namespace uking::action {

ForkSeparateThreeASPart::ForkSeparateThreeASPart(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSeparateThreeASPart::~ForkSeparateThreeASPart() = default;

bool ForkSeparateThreeASPart::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSeparateThreeASPart::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkSeparateThreeASPart::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSeparateThreeASPart::loadParams_() {
    getStaticParam(&mRootNode_s, "RootNode");
    getStaticParam(&mSlot1StartNode_s, "Slot1StartNode");
    getStaticParam(&mSlot2StartNode_s, "Slot2StartNode");
}

void ForkSeparateThreeASPart::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
