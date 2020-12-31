#pragma once

#include "Game/AI/AI/aiWindGenerator.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WindGeneratorSignal : public WindGenerator {
    SEAD_RTTI_OVERRIDE(WindGeneratorSignal, WindGenerator)
public:
    explicit WindGeneratorSignal(const InitArg& arg);
    ~WindGeneratorSignal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
