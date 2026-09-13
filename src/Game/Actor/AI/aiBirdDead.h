#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BirdDead : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BirdDead, ksys::act::ai::Ai)
public:
    explicit BirdDead(const InitArg& arg);
    ~BirdDead() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mGravityScale_s{};
};

}  // namespace uking::ai
