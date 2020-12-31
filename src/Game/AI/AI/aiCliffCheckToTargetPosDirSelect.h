#pragma once

#include "Game/AI/AI/aiCliffCheckSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CliffCheckToTargetPosDirSelect : public CliffCheckSelect {
    SEAD_RTTI_OVERRIDE(CliffCheckToTargetPosDirSelect, CliffCheckSelect)
public:
    explicit CliffCheckToTargetPosDirSelect(const InitArg& arg);
    ~CliffCheckToTargetPosDirSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
