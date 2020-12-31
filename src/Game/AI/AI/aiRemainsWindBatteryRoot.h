#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsWindBatteryRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsWindBatteryRoot, ksys::act::ai::Ai)
public:
    explicit RemainsWindBatteryRoot(const InitArg& arg);
    ~RemainsWindBatteryRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
