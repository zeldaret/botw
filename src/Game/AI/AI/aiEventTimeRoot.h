#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EventTimeRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EventTimeRoot, ksys::act::ai::Ai)
public:
    explicit EventTimeRoot(const InitArg& arg);
    ~EventTimeRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mTimeLimit_s{};
    // static_param at offset 0x40
    const bool* mIsCountDown_s{};
};

}  // namespace uking::ai
