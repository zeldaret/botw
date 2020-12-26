#pragma once

#include "Game/AI/Action/actionThrown.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ThrownAndBreak : public Thrown {
    SEAD_RTTI_OVERRIDE(ThrownAndBreak, Thrown)
public:
    explicit ThrownAndBreak(const InitArg& arg);
    ~ThrownAndBreak() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
