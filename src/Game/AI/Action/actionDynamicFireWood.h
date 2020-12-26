#pragma once

#include "Game/AI/Action/actionFireWood.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DynamicFireWood : public FireWood {
    SEAD_RTTI_OVERRIDE(DynamicFireWood, FireWood)
public:
    explicit DynamicFireWood(const InitArg& arg);
    ~DynamicFireWood() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
