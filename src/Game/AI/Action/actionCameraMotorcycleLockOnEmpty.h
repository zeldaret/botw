#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraMotorcycleLockOnEmpty : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraMotorcycleLockOnEmpty, CameraAction)
public:
    explicit CameraMotorcycleLockOnEmpty(const InitArg& arg);
    ~CameraMotorcycleLockOnEmpty() override;

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
