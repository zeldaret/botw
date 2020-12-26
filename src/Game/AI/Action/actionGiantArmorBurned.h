#pragma once

#include "Game/AI/Action/actionGiantArmorAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantArmorBurned : public GiantArmorAction {
    SEAD_RTTI_OVERRIDE(GiantArmorBurned, GiantArmorAction)
public:
    explicit GiantArmorBurned(const InitArg& arg);
    ~GiantArmorBurned() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
