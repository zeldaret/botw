#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetBeatCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetBeatCheck, ksys::act::ai::Ai)
public:
    explicit TargetBeatCheck(const InitArg& arg);
    ~TargetBeatCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
