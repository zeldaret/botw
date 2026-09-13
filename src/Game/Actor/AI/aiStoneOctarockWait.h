#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StoneOctarockWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StoneOctarockWait, ksys::act::ai::Ai)
public:
    explicit StoneOctarockWait(const InitArg& arg);
    ~StoneOctarockWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mGuardEndTime_s{};
    // static_param at offset 0x40
    const int* mNoticeTerrorLevel_s{};
};

}  // namespace uking::ai
