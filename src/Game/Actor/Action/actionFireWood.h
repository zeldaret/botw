#pragma once

#include "Game/Actor/Action/actionFireBurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FireWood : public FireBurnBase {
    SEAD_RTTI_OVERRIDE(FireWood, FireBurnBase)
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
