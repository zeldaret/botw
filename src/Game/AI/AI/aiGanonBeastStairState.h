#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonBeastStairState : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonBeastStairState, ksys::act::ai::Ai)
public:
    explicit GanonBeastStairState(const InitArg& arg);
    ~GanonBeastStairState() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
