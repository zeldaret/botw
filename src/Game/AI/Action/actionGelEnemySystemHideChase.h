#pragma once

#include "Game/AI/Action/actionSystemHideChase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GelEnemySystemHideChase : public SystemHideChase {
    SEAD_RTTI_OVERRIDE(GelEnemySystemHideChase, SystemHideChase)
public:
    explicit GelEnemySystemHideChase(const InitArg& arg);
    ~GelEnemySystemHideChase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
