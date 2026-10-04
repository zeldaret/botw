#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalPartNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalPartNormal, ksys::act::ai::Ai)
public:
    explicit StalPartNormal(const InitArg& arg);
    ~StalPartNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTerritoryArea_s{};
    // static_param at offset 0x40
    const float* mCatchArea_s{};
    // static_param at offset 0x48
    const float* mWaitTimer_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mTgtOffset_s{};
};

}  // namespace uking::ai
