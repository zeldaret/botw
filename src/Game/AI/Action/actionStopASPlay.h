#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StopASPlay : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(StopASPlay, ActionWithPosAngReduce)
public:
    explicit StopASPlay(const InitArg& arg);
    ~StopASPlay() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
