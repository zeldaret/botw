#include "Game/AI/AI/aiSeqPursuit.h"

namespace uking::ai {

SeqPursuit::SeqPursuit(const InitArg& arg) : SeqTwoAction(arg) {}

SeqPursuit::~SeqPursuit() = default;

bool SeqPursuit::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void SeqPursuit::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void SeqPursuit::leave_() {
    SeqTwoAction::leave_();
}

void SeqPursuit::loadParams_() {
    SeqTwoAction::loadParams_();
    getStaticParam(&mPursuitPer_s, "PursuitPer");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mPursuitDist_s, "PursuitDist");
    getStaticParam(&mIsEndPursuit_s, "IsEndPursuit");
    getStaticParam(&mIsGuardNoPursuit_s, "IsGuardNoPursuit");
}

}  // namespace uking::ai
