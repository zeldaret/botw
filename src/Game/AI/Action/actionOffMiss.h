#pragma once

#include "Game/AI/Action/actionOff.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OffMiss : public Off {
    SEAD_RTTI_OVERRIDE(OffMiss, Off)
public:
    explicit OffMiss(const InitArg& arg);
    ~OffMiss() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
