#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RailMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RailMove, ksys::act::ai::Ai)
public:
    explicit RailMove(const InitArg& arg);
    ~RailMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsIgnoreNoWaitStopPoint_s{};
};

}  // namespace uking::ai
