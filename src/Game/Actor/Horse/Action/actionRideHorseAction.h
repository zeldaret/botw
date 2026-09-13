#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RideHorseAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RideHorseAction, ksys::act::ai::Action)
public:
    explicit RideHorseAction(const InitArg& arg);
    ~RideHorseAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    ksys::act::BaseProcLink* mHorse_d{};
};

}  // namespace uking::action
