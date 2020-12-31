#pragma once

#include "Game/AI/AI/aiDragonRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DragonFireRoot : public DragonRoot {
    SEAD_RTTI_OVERRIDE(DragonFireRoot, DragonRoot)
public:
    explicit DragonFireRoot(const InitArg& arg);
    ~DragonFireRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
