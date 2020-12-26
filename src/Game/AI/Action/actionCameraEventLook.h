#pragma once

#include "Game/AI/Action/actionCameraEventLookBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventLook : public CameraEventLookBase {
    SEAD_RTTI_OVERRIDE(CameraEventLook, CameraEventLookBase)
public:
    explicit CameraEventLook(const InitArg& arg);
    ~CameraEventLook() override;

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
