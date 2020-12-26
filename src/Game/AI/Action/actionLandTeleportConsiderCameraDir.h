#pragma once

#include "Game/AI/Action/actionLandTeleport.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LandTeleportConsiderCameraDir : public LandTeleport {
    SEAD_RTTI_OVERRIDE(LandTeleportConsiderCameraDir, LandTeleport)
public:
    explicit LandTeleportConsiderCameraDir(const InitArg& arg);
    ~LandTeleportConsiderCameraDir() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const float* mCameraDirCoeff_s{};
};

}  // namespace uking::action
