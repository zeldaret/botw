#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetDirectionalLight : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetDirectionalLight, ksys::act::ai::Action)
public:
    explicit EventSetDirectionalLight(const InitArg& arg);
    ~EventSetDirectionalLight() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mangleX_d{};
    // dynamic_param at offset 0x28
    float* mangleY_d{};
};

}  // namespace uking::action
