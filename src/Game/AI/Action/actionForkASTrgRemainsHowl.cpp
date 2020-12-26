#include "Game/AI/Action/actionForkASTrgRemainsHowl.h"

namespace uking::action {

ForkASTrgRemainsHowl::ForkASTrgRemainsHowl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgRemainsHowl::~ForkASTrgRemainsHowl() = default;

bool ForkASTrgRemainsHowl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgRemainsHowl::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASTrgRemainsHowl::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgRemainsHowl::loadParams_() {
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getDynamicParam(&mIsTargetLost_d, "IsTargetLost");
}

void ForkASTrgRemainsHowl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
