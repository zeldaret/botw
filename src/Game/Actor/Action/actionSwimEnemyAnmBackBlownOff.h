#pragma once

#include "Game/Actor/Action/actionSwimEnemyBlownOffBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimEnemyAnmBackBlownOff : public SwimEnemyBlownOffBase {
    SEAD_RTTI_OVERRIDE(SwimEnemyAnmBackBlownOff, SwimEnemyBlownOffBase)
public:
    explicit SwimEnemyAnmBackBlownOff(const InitArg& arg);
    ~SwimEnemyAnmBackBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const float* mRotSpeed_s{};
};

}  // namespace uking::action
