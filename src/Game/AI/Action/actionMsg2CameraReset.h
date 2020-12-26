#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Msg2CameraReset : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Msg2CameraReset, ksys::act::ai::Action)
public:
    explicit Msg2CameraReset(const InitArg& arg);
    ~Msg2CameraReset() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
