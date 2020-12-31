#pragma once

#include "Game/AI/AI/aiSiteBossShootNormalArrowRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossReflectArrowRoot : public SiteBossShootNormalArrowRoot {
    SEAD_RTTI_OVERRIDE(SiteBossReflectArrowRoot, SiteBossShootNormalArrowRoot)
public:
    explicit SiteBossReflectArrowRoot(const InitArg& arg);
    ~SiteBossReflectArrowRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x338
    bool* mIsReflectAmongChild_d{};
    // dynamic_param at offset 0x340
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
