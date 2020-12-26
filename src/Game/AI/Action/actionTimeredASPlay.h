#pragma once

#include "Game/AI/Action/actionWaitBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TimeredASPlay : public WaitBase {
    SEAD_RTTI_OVERRIDE(TimeredASPlay, WaitBase)
public:
    explicit TimeredASPlay(const InitArg& arg);
    ~TimeredASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
