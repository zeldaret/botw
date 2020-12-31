#pragma once

#include "Game/AI/AI/aiRemainsRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsWindRoot : public RemainsRoot {
    SEAD_RTTI_OVERRIDE(RemainsWindRoot, RemainsRoot)
public:
    explicit RemainsWindRoot(const InitArg& arg);
    ~RemainsWindRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
