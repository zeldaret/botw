#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Notice : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(Notice, ActionWithAS)
public:
    explicit Notice(const InitArg& arg);
    ~Notice() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x28
    const float* mAngReduceRatio_s{};
};

}  // namespace uking::action
