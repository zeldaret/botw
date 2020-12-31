#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class JustAvoidFinishWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(JustAvoidFinishWait, ksys::act::ai::Ai)
public:
    explicit JustAvoidFinishWait(const InitArg& arg);
    ~JustAvoidFinishWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsUseWaitAfterMain_s{};
};

}  // namespace uking::ai
