#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqFirstPointTwo : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqFirstPointTwo, ksys::act::ai::Ai)
public:
    explicit SeqFirstPointTwo(const InitArg& arg);
    ~SeqFirstPointTwo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsFinishedByFailAction_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
