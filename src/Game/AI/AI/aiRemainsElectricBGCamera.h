#pragma once

#include "Game/AI/AI/aiRailMoveRemainsBGCamera.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsElectricBGCamera : public RailMoveRemainsBGCamera {
    SEAD_RTTI_OVERRIDE(RemainsElectricBGCamera, RailMoveRemainsBGCamera)
public:
    explicit RemainsElectricBGCamera(const InitArg& arg);
    ~RemainsElectricBGCamera() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x108
    sead::SafeString mParentActorName_s{};
};

}  // namespace uking::ai
