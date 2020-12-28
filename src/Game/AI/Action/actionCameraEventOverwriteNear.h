#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventOverwriteNear : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraEventOverwriteNear, ksys::act::ai::Action)
public:
    explicit CameraEventOverwriteNear(const InitArg& arg);
    ~CameraEventOverwriteNear() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x20[0x10];
    // dynamic2_param at offset 0x30
    float* mNear_d{};
};

}  // namespace uking::action
