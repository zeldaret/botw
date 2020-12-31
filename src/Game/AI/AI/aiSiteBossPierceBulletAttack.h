#pragma once

#include "Game/AI/AI/aiSiteBossShootNormalArrowRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossPierceBulletAttack : public SiteBossShootNormalArrowRoot {
    SEAD_RTTI_OVERRIDE(SiteBossPierceBulletAttack, SiteBossShootNormalArrowRoot)
public:
    explicit SiteBossPierceBulletAttack(const InitArg& arg);
    ~SiteBossPierceBulletAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
};

}  // namespace uking::ai
