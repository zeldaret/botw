#pragma once

#include "Game/AI/Action/actionGetItem.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GetCapturedActor : public GetItem {
    SEAD_RTTI_OVERRIDE(GetCapturedActor, GetItem)
public:
    explicit GetCapturedActor(const InitArg& arg);
    ~GetCapturedActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
