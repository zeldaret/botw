#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SystemFadeOutSleep : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SystemFadeOutSleep, ksys::act::ai::Action)
public:
    explicit SystemFadeOutSleep(const InitArg& arg);
    ~SystemFadeOutSleep() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
