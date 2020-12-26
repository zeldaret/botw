#pragma once

#include "Game/AI/Action/actionBindActionForManyActor.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BindActionUseParentPickInfo : public BindActionForManyActor {
    SEAD_RTTI_OVERRIDE(BindActionUseParentPickInfo, BindActionForManyActor)
public:
    explicit BindActionUseParentPickInfo(const InitArg& arg);
    ~BindActionUseParentPickInfo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
