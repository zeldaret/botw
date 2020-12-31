#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PrevASOR2SelectTwo : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PrevASOR2SelectTwo, ksys::act::ai::Ai)
public:
    explicit PrevASOR2SelectTwo(const InitArg& arg);
    ~PrevASOR2SelectTwo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    sead::SafeString mAS1_s{};
    // static_param at offset 0x48
    sead::SafeString mAS2_s{};
};

}  // namespace uking::ai
