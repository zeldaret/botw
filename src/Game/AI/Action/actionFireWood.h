#pragma once

#include "Game/AI/Action/actionFireWoodBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FireWood : public FireWoodBase {
    SEAD_RTTI_OVERRIDE(FireWood, FireWoodBase)
public:
    explicit FireWood(const InitArg& arg);
    ~FireWood() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
