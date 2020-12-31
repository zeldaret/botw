#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PrevASEndSeq : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PrevASEndSeq, ksys::act::ai::Ai)
public:
    explicit PrevASEndSeq(const InitArg& arg);
    ~PrevASEndSeq() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    sead::SafeString mPrevASName_s{};
};

}  // namespace uking::ai
