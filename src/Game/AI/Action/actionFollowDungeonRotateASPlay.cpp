#include "Game/AI/Action/actionFollowDungeonRotateASPlay.h"

namespace uking::action {

FollowDungeonRotateASPlay::FollowDungeonRotateASPlay(const InitArg& arg)
    : FollowDungeonRotate(arg) {}

FollowDungeonRotateASPlay::~FollowDungeonRotateASPlay() = default;

bool FollowDungeonRotateASPlay::init_(sead::Heap* heap) {
    return FollowDungeonRotate::init_(heap);
}

void FollowDungeonRotateASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    FollowDungeonRotate::enter_(params);
}

void FollowDungeonRotateASPlay::leave_() {
    FollowDungeonRotate::leave_();
}

void FollowDungeonRotateASPlay::loadParams_() {
    FollowDungeonRotate::loadParams_();
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mIsSuccessEndOnASFinish_s, "IsSuccessEndOnASFinish");
    getStaticParam(&mOnWaitRevival_s, "OnWaitRevival");
    getStaticParam(&mOnLinkTagBasic_s, "OnLinkTagBasic");
    getStaticParam(&mASName_s, "ASName");
}

void FollowDungeonRotateASPlay::calc_() {
    FollowDungeonRotate::calc_();
}

}  // namespace uking::action
