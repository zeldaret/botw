#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventIdling : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventIdling, CameraEvent)
public:
    explicit CameraEventIdling(const InitArg& arg);
    ~CameraEventIdling() override;

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
