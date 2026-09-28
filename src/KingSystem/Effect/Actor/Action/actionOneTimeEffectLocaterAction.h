#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::eft {

class OneTimeEffectLocaterAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(OneTimeEffectLocaterAction, ksys::act::ai::Action)
public:
    explicit OneTimeEffectLocaterAction(const InitArg& arg);
    ~OneTimeEffectLocaterAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace ksys::eft
