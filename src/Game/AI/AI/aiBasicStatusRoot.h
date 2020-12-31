#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BasicStatusRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BasicStatusRoot, ksys::act::ai::Ai)
public:
    explicit BasicStatusRoot(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
