#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StartupTelescope : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StartupTelescope, ksys::act::ai::Action)
public:
    explicit StartupTelescope(const InitArg& arg);
    ~StartupTelescope() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
