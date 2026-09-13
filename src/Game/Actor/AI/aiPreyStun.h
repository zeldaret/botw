#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PreyStun : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PreyStun, ksys::act::ai::Ai)
public:
    explicit PreyStun(const InitArg& arg);
    ~PreyStun() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mStunTime_s{};
};

}  // namespace uking::ai
