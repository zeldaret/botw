#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act::ai {

class DemoRootAI : public Ai {
    SEAD_RTTI_OVERRIDE(DemoRootAI, Ai)
public:
    explicit DemoRootAI(const InitArg& arg);
    ~DemoRootAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace ksys::act::ai
