#pragma once

#include "Game/AI/AI/aiGiantArmorRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GiantArmorAsWeakPoint : public GiantArmorRoot {
    SEAD_RTTI_OVERRIDE(GiantArmorAsWeakPoint, GiantArmorRoot)
public:
    explicit GiantArmorAsWeakPoint(const InitArg& arg);
    ~GiantArmorAsWeakPoint() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
