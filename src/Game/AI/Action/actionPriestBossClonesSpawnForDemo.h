#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PriestBossClonesSpawnForDemo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PriestBossClonesSpawnForDemo, ksys::act::ai::Action)
public:
    explicit PriestBossClonesSpawnForDemo(const InitArg& arg);
    ~PriestBossClonesSpawnForDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mDurationFrame_d{};
    // dynamic_param at offset 0x28
    int* mDecelerationFrame_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mASName_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mOffset_d{};
    // aitree_variable at offset 0x48
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::action
