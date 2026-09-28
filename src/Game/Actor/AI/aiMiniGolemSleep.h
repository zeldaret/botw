#pragma once

#include "Game/Actor/AI/aiSleepNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MiniGolemSleep : public SleepNormal {
    SEAD_RTTI_OVERRIDE(MiniGolemSleep, SleepNormal)
public:
    explicit MiniGolemSleep(const InitArg& arg);
    ~MiniGolemSleep() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x60
    void* mGolemChemicalController_a{};
};

}  // namespace uking::ai
