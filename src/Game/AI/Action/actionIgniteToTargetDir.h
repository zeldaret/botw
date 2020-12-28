#pragma once

#include "Game/AI/Action/actionIgniteToTargetSimple.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IgniteToTargetDir : public IgniteToTargetSimple {
    SEAD_RTTI_OVERRIDE(IgniteToTargetDir, IgniteToTargetSimple)
public:
    explicit IgniteToTargetDir(const InitArg& arg);
    ~IgniteToTargetDir() override;

    void loadParams_() override;

protected:
};

}  // namespace uking::action
