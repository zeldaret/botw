#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Lifted : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(Lifted, ksys::act::ai::Ai)
public:
    explicit Lifted(const InitArg& arg);
    ~Lifted() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsGetItem_s{};
};

}  // namespace uking::ai
