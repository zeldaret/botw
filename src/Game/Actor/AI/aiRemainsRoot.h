#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsRoot, ksys::act::ai::Ai)
public:
    explicit RemainsRoot(const InitArg& arg);
    ~RemainsRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mRemainsTypeID_s{};
    // static_param at offset 0x40
    const bool* mIsAllowRotAxisX_s{};
};

}  // namespace uking::ai
