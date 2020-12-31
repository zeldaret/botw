#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SwitchAI, ksys::act::ai::Ai)
public:
    explicit SwitchAI(const InitArg& arg);
    ~SwitchAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
