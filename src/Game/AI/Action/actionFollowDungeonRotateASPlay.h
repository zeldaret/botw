#pragma once

#include "Game/AI/Action/actionFollowDungeonRotate.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FollowDungeonRotateASPlay : public FollowDungeonRotate {
    SEAD_RTTI_OVERRIDE(FollowDungeonRotateASPlay, FollowDungeonRotate)
public:
    explicit FollowDungeonRotateASPlay(const InitArg& arg);
    ~FollowDungeonRotateASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mTargetIdx_s{};
    // static_param at offset 0x38
    const int* mSeqBankIdx_s{};
    // static_param at offset 0x40
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0x48
    const bool* mIsSuccessEndOnASFinish_s{};
    // static_param at offset 0x50
    const bool* mOnWaitRevival_s{};
    // static_param at offset 0x58
    const bool* mOnLinkTagBasic_s{};
    // static_param at offset 0x60
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
