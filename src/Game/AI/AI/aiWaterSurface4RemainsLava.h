#pragma once

#include "Game/AI/AI/aiWaterSurface.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WaterSurface4RemainsLava : public WaterSurface {
    SEAD_RTTI_OVERRIDE(WaterSurface4RemainsLava, WaterSurface)
public:
    explicit WaterSurface4RemainsLava(const InitArg& arg);
    ~WaterSurface4RemainsLava() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
