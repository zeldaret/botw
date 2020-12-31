#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossThrowIceRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossThrowIceRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossThrowIceRoot(const InitArg& arg);
    ~SiteBossThrowIceRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mIgnitionNum_s{};
    // static_param at offset 0x40
    sead::SafeString mThrowActorName_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x58
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
