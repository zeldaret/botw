#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventMovePosBase : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventMovePosBase, CameraEvent)
public:
    explicit CameraEventMovePosBase(const InitArg& arg);
    ~CameraEventMovePosBase() override;

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
