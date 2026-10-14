#pragma once

#include "Game/Actor/Area/Action/actionAreaActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SandwichDetectionAreaTag : public AreaActionBase {
    SEAD_RTTI_OVERRIDE(SandwichDetectionAreaTag, AreaActionBase)
public:
    explicit SandwichDetectionAreaTag(const InitArg& arg);
    ~SandwichDetectionAreaTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
