#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetStateSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetStateSelect, ksys::act::ai::Ai)
public:
    explicit TargetStateSelect(const InitArg& arg);
    ~TargetStateSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
