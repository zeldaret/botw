#pragma once

#include "Game/Actor/Action/actionASPlayRotateTurnToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NoticeTurn : public ASPlayRotateTurnToTarget {
    SEAD_RTTI_OVERRIDE(NoticeTurn, ASPlayRotateTurnToTarget)
public:
    explicit NoticeTurn(const InitArg& arg);
    ~NoticeTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    const int* mNoDoubleNoticeTime_s{};
};

}  // namespace uking::action
