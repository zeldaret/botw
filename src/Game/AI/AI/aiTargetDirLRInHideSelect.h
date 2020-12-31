#pragma once

#include "Game/AI/AI/aiTargetDirLRSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetDirLRInHideSelect : public TargetDirLRSelect {
    SEAD_RTTI_OVERRIDE(TargetDirLRInHideSelect, TargetDirLRSelect)
public:
    explicit TargetDirLRInHideSelect(const InitArg& arg);
    ~TargetDirLRInHideSelect() override;

protected:
};

}  // namespace uking::ai
