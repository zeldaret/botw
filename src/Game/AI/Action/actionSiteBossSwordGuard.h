#pragma once

#include "Game/AI/Action/actionGuard.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordGuard : public Guard {
    SEAD_RTTI_OVERRIDE(SiteBossSwordGuard, Guard)
public:
    explicit SiteBossSwordGuard(const InitArg& arg);
    ~SiteBossSwordGuard() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
