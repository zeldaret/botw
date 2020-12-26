#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventOverwriteFar : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraEventOverwriteFar, ksys::act::ai::Action)
public:
    explicit CameraEventOverwriteFar(const InitArg& arg);
    ~CameraEventOverwriteFar() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0x10];
    // dynamic2_param at offset 0x30
    float* mFar_d{};
};

}  // namespace uking::action
