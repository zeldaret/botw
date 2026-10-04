#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BalloonPlantNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BalloonPlantNormal, ksys::act::ai::Ai)
public:
    explicit BalloonPlantNormal(const InitArg& arg);
    ~BalloonPlantNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRopeLength_s{};
    // static_param at offset 0x40
    sead::SafeString mRopeActorName_s{};
};

}  // namespace uking::ai
