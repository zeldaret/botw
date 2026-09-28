#pragma once

#include "Game/Actor/AI/aiSleepNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemSleepNormal : public SleepNormal {
    SEAD_RTTI_OVERRIDE(GolemSleepNormal, SleepNormal)
public:
    explicit GolemSleepNormal(const InitArg& arg);
    ~GolemSleepNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x60
    void* mGolemChemicalController_a{};
};

}  // namespace uking::ai
