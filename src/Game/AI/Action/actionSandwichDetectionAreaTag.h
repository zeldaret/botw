#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SandwichDetectionAreaTag : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(SandwichDetectionAreaTag, AreaTagAction)
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
