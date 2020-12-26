#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SandwormASPlay : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(SandwormASPlay, ActionWithPosAngReduce)
public:
    explicit SandwormASPlay(const InitArg& arg);
    ~SandwormASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mChangeOffsetDelay_s{};
    // static_param at offset 0x38
    const float* mTargetSandOffset_s{};
    // static_param at offset 0x40
    const float* mSandOffsetSpeed_s{};
    // static_param at offset 0x48
    const bool* mWaitASFinish_s{};
    // static_param at offset 0x50
    const bool* mWaitSandOffset_s{};
    // static_param at offset 0x58
    const bool* mIsChangeable_s{};
    // static_param at offset 0x60
    const bool* mIsUseAtEvent_s{};
    // static_param at offset 0x68
    const bool* mIsUseTossAt_s{};
    // static_param at offset 0x70
    sead::SafeString mASName_s{};
    // static_param at offset 0x80
    sead::SafeString mTransBoneName_s{};
};

}  // namespace uking::action
