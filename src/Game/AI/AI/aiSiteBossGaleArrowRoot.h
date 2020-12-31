#pragma once

#include "Game/AI/AI/aiWithoutWeaponArrow.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossGaleArrowRoot : public WithoutWeaponArrow {
    SEAD_RTTI_OVERRIDE(SiteBossGaleArrowRoot, WithoutWeaponArrow)
public:
    explicit SiteBossGaleArrowRoot(const InitArg& arg);
    ~SiteBossGaleArrowRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
