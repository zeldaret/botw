#include "Game/AI/Action/actionForkStalEnemyGrabOwnPart.h"

namespace uking::action {

ForkStalEnemyGrabOwnPart::ForkStalEnemyGrabOwnPart(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkStalEnemyGrabOwnPart::~ForkStalEnemyGrabOwnPart() = default;

bool ForkStalEnemyGrabOwnPart::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkStalEnemyGrabOwnPart::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkStalEnemyGrabOwnPart::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkStalEnemyGrabOwnPart::loadParams_() {
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mBoneName_s, "BoneName");
    getDynamicParam(&mPartIndex_d, "PartIndex");
}

void ForkStalEnemyGrabOwnPart::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
