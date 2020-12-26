#include "Game/AI/Action/actionForkBoneControlFrontGround.h"

namespace uking::action {

ForkBoneControlFrontGround::ForkBoneControlFrontGround(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkBoneControlFrontGround::~ForkBoneControlFrontGround() = default;

bool ForkBoneControlFrontGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkBoneControlFrontGround::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkBoneControlFrontGround::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkBoneControlFrontGround::loadParams_() {
    getStaticParam(&mTargetOffset_s, "TargetOffset");
}

void ForkBoneControlFrontGround::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
