#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorsePrevRiddenStatusSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorsePrevRiddenStatusSelector, ksys::act::ai::Ai)
public:
    explicit HorsePrevRiddenStatusSelector(const InitArg& arg);
    ~HorsePrevRiddenStatusSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
