#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventReserveConnectTime : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraEventReserveConnectTime, ksys::act::ai::Action)
public:
    explicit CameraEventReserveConnectTime(const InitArg& arg);
    ~CameraEventReserveConnectTime() override;

    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x20[0x10];
    // dynamic2_param at offset 0x30
    float* mInterpolateTime_d{};
};

}  // namespace uking::action
