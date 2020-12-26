#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SandwichDetectionAreaTagSimple : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(SandwichDetectionAreaTagSimple, AreaTagAction)
public:
    explicit SandwichDetectionAreaTagSimple(const InitArg& arg);
    ~SandwichDetectionAreaTagSimple() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
