#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetDirLRSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetDirLRSelect, ksys::act::ai::Ai)
public:
    explicit TargetDirLRSelect(const InitArg& arg);
    ~TargetDirLRSelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::ai
