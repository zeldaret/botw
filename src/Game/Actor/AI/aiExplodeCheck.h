#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ExplodeCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ExplodeCheck, ksys::act::ai::Ai)
public:
    explicit ExplodeCheck(const InitArg& arg);
    ~ExplodeCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
