#pragma once

#include "Game/AI/Action/actionIgniteToTargetSimple.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IgniteToTargetDir : public IgniteToTargetSimple {
    SEAD_RTTI_OVERRIDE(IgniteToTargetDir, IgniteToTargetSimple)
public:
    explicit IgniteToTargetDir(const InitArg& arg);
    ~IgniteToTargetDir() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
