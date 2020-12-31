#include "Game/AI/AI/aiSeqCloseDistTwoAction.h"

namespace uking::ai {

SeqCloseDistTwoAction::SeqCloseDistTwoAction(const InitArg& arg) : SeqTwoAction(arg) {}

SeqCloseDistTwoAction::~SeqCloseDistTwoAction() = default;

void SeqCloseDistTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void SeqCloseDistTwoAction::loadParams_() {
    SeqTwoAction::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
