#pragma once

#include "Game/AI/AI/aiPreyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PreyDropItemRoot : public PreyRoot {
    SEAD_RTTI_OVERRIDE(PreyDropItemRoot, PreyRoot)
public:
    explicit PreyDropItemRoot(const InitArg& arg);
    ~PreyDropItemRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x208
    const int* mMaxDropCount_s{};
    // static_param at offset 0x210
    const float* mForceDeleteInterval_s{};
    // static_param at offset 0x218
    const sead::Vector3f* mInitialVelocity_s{};
};

}  // namespace uking::ai
