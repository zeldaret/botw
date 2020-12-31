#pragma once

#include "Game/AI/AI/aiSpecialEnemySleep.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemSleepNormal : public SpecialEnemySleep {
    SEAD_RTTI_OVERRIDE(GolemSleepNormal, SpecialEnemySleep)
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
