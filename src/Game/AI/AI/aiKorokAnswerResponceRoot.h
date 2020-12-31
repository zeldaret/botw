#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KorokAnswerResponceRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokAnswerResponceRoot, ksys::act::ai::Ai)
public:
    explicit KorokAnswerResponceRoot(const InitArg& arg);
    ~KorokAnswerResponceRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const float* mEffectDispSize_m{};
    // map_unit_param at offset 0x40
    const bool* mIsNoResponceSound_m{};
    // map_unit_param at offset 0x48
    sead::SafeString mEffectDispActorName_m{};
    // map_unit_param at offset 0x58
    const sead::Vector3f* mEffectDIspOffset_m{};
};

}  // namespace uking::ai
