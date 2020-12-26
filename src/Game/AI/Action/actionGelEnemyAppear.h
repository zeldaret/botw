#pragma once

#include "Game/AI/Action/actionAppear.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GelEnemyAppear : public Appear {
    SEAD_RTTI_OVERRIDE(GelEnemyAppear, Appear)
public:
    explicit GelEnemyAppear(const InitArg& arg);
    ~GelEnemyAppear() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
