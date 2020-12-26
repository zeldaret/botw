#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Msg2CameraResetNoConnect : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Msg2CameraResetNoConnect, ksys::act::ai::Action)
public:
    explicit Msg2CameraResetNoConnect(const InitArg& arg);
    ~Msg2CameraResetNoConnect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
