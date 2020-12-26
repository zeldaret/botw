#pragma once

#include "Game/AI/Action/actionSiteBossSwordAttackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordWhirlSlash : public SiteBossSwordAttackBase {
    SEAD_RTTI_OVERRIDE(SiteBossSwordWhirlSlash, SiteBossSwordAttackBase)
public:
    explicit SiteBossSwordWhirlSlash(const InitArg& arg);
    ~SiteBossSwordWhirlSlash() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
