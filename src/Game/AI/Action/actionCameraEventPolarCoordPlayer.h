#pragma once

#include "Game/AI/Action/actionCameraEventPolarCoord.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventPolarCoordPlayer : public CameraEventPolarCoord {
    SEAD_RTTI_OVERRIDE(CameraEventPolarCoordPlayer, CameraEventPolarCoord)
public:
    explicit CameraEventPolarCoordPlayer(const InitArg& arg);
    ~CameraEventPolarCoordPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x40
    const bool* mBowFlag_s{};
};

}  // namespace uking::action
