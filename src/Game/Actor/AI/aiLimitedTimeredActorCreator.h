#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LimitedTimeredActorCreator : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LimitedTimeredActorCreator, ksys::act::ai::Ai)
public:
    explicit LimitedTimeredActorCreator(const InitArg& arg);
    ~LimitedTimeredActorCreator() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mCreateTimer_s{};
    // static_param at offset 0x40
    const float* mCreateTimerRand_s{};
    // static_param at offset 0x48
    sead::SafeString mCreateActorName_s{};
    // map_unit_param at offset 0x58
    const int* mCreateLimit_m{};
    // map_unit_param at offset 0x60
    sead::SafeString mActorName_m{};
    // aitree_variable at offset 0x70
    void* mGeneratedActorLink_a{};
};

}  // namespace uking::ai
