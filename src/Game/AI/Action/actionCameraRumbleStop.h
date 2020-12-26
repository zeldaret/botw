#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraRumbleStop : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraRumbleStop, ksys::act::ai::Action)
public:
    explicit CameraRumbleStop(const InitArg& arg);
    ~CameraRumbleStop() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    int* mCamVibId_a{};
};

}  // namespace uking::action
