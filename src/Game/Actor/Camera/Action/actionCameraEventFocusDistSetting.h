#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventFocusDistSetting : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraEventFocusDistSetting, ksys::act::ai::Action)
public:
    explicit CameraEventFocusDistSetting(const InitArg& arg);
    ~CameraEventFocusDistSetting() override;

    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0x10];
    // dynamic2_param at offset 0x30
    int* mClipIndex_d{};
    // dynamic2_param at offset 0x38
    float* mFocusDistStart_d{};
    // dynamic2_param at offset 0x40
    float* mFocusDistEnd_d{};
};

}  // namespace uking::action
