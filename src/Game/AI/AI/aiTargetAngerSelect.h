#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetAngerSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetAngerSelect, ksys::act::ai::Ai)
public:
    explicit TargetAngerSelect(const InitArg& arg);
    ~TargetAngerSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
