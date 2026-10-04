#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DieSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DieSelect, ksys::act::ai::Ai)
public:
    explicit DieSelect(const InitArg& arg);
    ~DieSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
